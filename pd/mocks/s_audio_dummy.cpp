/*
 * Copyright (c) 2010 Peter Brinkmann (peter.brinkmann@gmail.com)
 *
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <memory>
#include <mutex>
#include <set>
#include <thread>

#include "RtAudio.h"
#include "ring_buffer.h"

#include "m_pd.h"
extern "C" {
#include "s_stuff.h"
}

extern "C" int mmio_open_audio(int naudioindev, int* audioindev,
    int nchindev, int* chindev, int naudiooutdev, int* audiooutdev,
    int nchoutdev, int* choutdev, int rate, int blocksize);
extern "C" void mmio_close_audio(void);
extern "C" void mmio_reportidle(void);
extern "C" int mmio_send_dacs(void);
extern "C" void mmio_getdevs(char* indevlist, int* nindevs,
    char* outdevlist, int* noutdevs, int* canmulti,
    int maxndev, int devdescsize);

static RtAudio* rt_audio = nullptr;
static std::mutex rt_audio_mutex;

static size_t rt_inchans = 0;
static size_t rt_outchans = 0;

static_assert(sizeof(float) == sizeof(t_sample), "sizeof(float) != sizeof(t_sample)");

static RingBuffer<8192> input_ring_buffer;
static RingBuffer<8192> out_ring_buffer;

#define RT_AUDIO_DEBUG

static void rt_audio_init()
{
    if (rt_audio)
        return;

#if defined(__APPLE__)
    RtAudio::Api api = RtAudio::MACOSX_CORE;
#else
    RtAudio::Api api = RtAudio::UNSPECIFIED;
#endif

    rt_audio = new RtAudio(api);
}

// called from RtAudio
static int rt_callback(
    void* outputBuffer,
    void* inputBuffer,
    unsigned int nBufferFrames,
    double /*streamTime*/,
    RtAudioStreamStatus status,
    void* /*data*/)
{
    float* out_float_buffer = static_cast<float*>(outputBuffer);
    float* in_float_buffer = static_cast<float*>(inputBuffer);
    const size_t n_out_samples = nBufferFrames * rt_outchans;
    const size_t n_in_samples = nBufferFrames * rt_inchans;

    if (out_ring_buffer.read_available(n_out_samples)) { // has data

        if (outputBuffer) {
            // read samples from ring buffer to RtAudio
            out_ring_buffer.read(out_float_buffer, n_out_samples);
        }

        if (inputBuffer) {
            // write samples from RtAudio to ring buffer
            input_ring_buffer.write(in_float_buffer, n_in_samples);
        }

    } else {
        /* PD could not keep up; generate zeros */
        if (outputBuffer)
            std::fill(out_float_buffer, out_float_buffer + n_out_samples, 0);
    }

#ifdef RT_AUDIO_DEBUG

    if (status & RTAUDIO_INPUT_OVERFLOW)
        puts("input underflow");

    if (status & RTAUDIO_OUTPUT_UNDERFLOW)
        puts("output underflow");

#endif

    return 0;
}

template <class Func>
int findNthDeviceByPred(Func fn, int idx)
{
    // 0 - means default device
    int n = 0;

    const auto num_devices = rt_audio->getDeviceCount();

    // invalid index
    if (idx >= num_devices)
        return 0;

    for (size_t i = 0; i < num_devices; i++) {
        RtAudio::DeviceInfo info = rt_audio->getDeviceInfo(i);
        if (fn(&info)) {
            n++;
            if (idx == n)
                return i;
        }
    }

    return 0;
}

RtAudio::StreamParameters stream_input_params(int devIdx)
{
    RtAudio::StreamParameters params;
    params.firstChannel = 0;
    params.nChannels = STUFF->st_inchannels;
    params.deviceId = devIdx;

    // default input device requested
    if (devIdx < 1)
        params.deviceId = rt_audio->getDefaultInputDevice();

    auto func = [](RtAudio::DeviceInfo* d) { return d->inputChannels > 0; };
    auto rt_idx = findNthDeviceByPred(func, devIdx);
    if (rt_idx < 1) {
        auto def_dev = rt_audio->getDefaultInputDevice();
        error("Invalid input device: %d. Using default instead %d.", params.deviceId, def_dev);
        params.deviceId = def_dev;
    }

    RtAudio::DeviceInfo info = rt_audio->getDeviceInfo(rt_idx);

    // check for valid channel count
    if (info.probed) {
        if (params.nChannels > info.inputChannels) {
            error("Unsupported number of input channels: %d. Setting to max value: %d",
                params.nChannels, info.inputChannels);

            params.nChannels = info.inputChannels;
        }

        post("input device: %s", info.name.c_str());
    }

    return params;
}

RtAudio::StreamParameters stream_output_params(int devIdx)
{

    RtAudio::StreamParameters params;
    params.firstChannel = 0;
    params.nChannels = STUFF->st_outchannels;
    params.deviceId = devIdx;

    if (devIdx < 1)
        params.deviceId = rt_audio->getDefaultOutputDevice();

    auto func = [](RtAudio::DeviceInfo* d) { return d->outputChannels > 0; };
    auto rt_idx = findNthDeviceByPred(func, devIdx);
    if (rt_idx < 1) {
        auto def_dev = rt_audio->getDefaultOutputDevice();
        error("Invalid output device: %d. Using default instead %d.", params.deviceId, def_dev);
        params.deviceId = def_dev;
    }

    RtAudio::DeviceInfo info = rt_audio->getDeviceInfo(rt_idx);

    if (info.probed) {
        // check for valid channel count
        if (params.nChannels > info.outputChannels) {
            error("Unsupported number of input channels: %d. Setting to max value: %d",
                params.nChannels, info.outputChannels);

            params.nChannels = info.outputChannels;
        }

        post("output device: %s", info.name.c_str());
    }

    return params;
}

RtAudio::StreamOptions stream_options()
{
    RtAudio::StreamOptions options;

    options.flags = RTAUDIO_HOG_DEVICE;
    options.flags |= RTAUDIO_NONINTERLEAVED;
    //    options.flags |= RTAUDIO_MINIMIZE_LATENCY;
    options.flags |= RTAUDIO_SCHEDULE_REALTIME;
    return options;
}

static bool has_sample_rate(const std::vector<unsigned int>& vec, unsigned int sr)
{
    return std::find(vec.begin(), vec.end(), sr) != vec.end();
}

static int common_sample_rate(const std::vector<unsigned int>& vec0,
    const std::vector<unsigned int>& vec1)
{
    std::set<unsigned int> s1(std::begin(vec0), std::end(vec0));
    std::set<unsigned int> s2(std::begin(vec1), std::end(vec1));

    std::vector<unsigned int> out;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(out));
    return out.empty() ? -1 : out.back();
}

static bool check_sample_rate(int* rate, int inIdx, int outIdx)
{
    RtAudio::DeviceInfo in_info = rt_audio->getDeviceInfo(inIdx);
    RtAudio::DeviceInfo out_info = rt_audio->getDeviceInfo(outIdx);

    // check input sample rate
    bool in_found = has_sample_rate(in_info.sampleRates, *rate);
    // check output sample rate
    bool out_found = has_sample_rate(out_info.sampleRates, *rate);

    if (in_found && out_found)
        return true;

    if (in_info.preferredSampleRate == out_info.preferredSampleRate) {
        error("specified samplerate not supported: %d. Using preferred samplerate: %d",
            *rate, out_info.preferredSampleRate);

        *rate = out_info.preferredSampleRate;
        return true;
    }

    auto common_sr = common_sample_rate(in_info.sampleRates, out_info.sampleRates);

    if (common_sr < 0) {
        error("can't find supported samplerate both for input and output devices...");
        return false;
    }

    *rate = common_sr;
    return true;
}

int mmio_open_audio(int naudioindev, int* audioindev,
    int nchindev, int* chindev,
    int naudiooutdev, int* audiooutdev,
    int nchoutdev, int* choutdev,
    int rate, int blocksize)
{
    std::lock_guard<std::mutex> rt_lock(rt_audio_mutex);

    RtAudio::StreamParameters iParams = stream_input_params(naudioindev);
    RtAudio::StreamParameters oParams = stream_output_params(naudiooutdev);

    rt_inchans = STUFF->st_inchannels = iParams.nChannels;
    rt_outchans = STUFF->st_outchannels = oParams.nChannels;

    RtAudio::StreamOptions options = stream_options();

    if (!check_sample_rate(&rate, iParams.deviceId, oParams.deviceId)) {
        error("unsupported sample rate: %d", rate);
    }

    // ????
    STUFF->st_dacsr = rate;
    unsigned int bufferFrames = blocksize;

    try {
        auto o_params = oParams.nChannels ? &oParams : nullptr;
        auto in_params = iParams.nChannels ? &iParams : nullptr;

        rt_audio->openStream(o_params, in_params, RTAUDIO_FLOAT32,
            rate, &bufferFrames, rt_callback, nullptr, &options);

        post("in/out buffer size: %d", bufferFrames);

        rt_audio->startStream();
    } catch (RtAudioError& e) {
        e.printMessage();

        if (rt_audio->isStreamOpen())
            rt_audio->closeStream();

        return 1;
    }

    // Test RtAudio functionality for reporting latency.
    //    std::cout << "\nStream latency = " << rt_audio->getStreamLatency() << " frames" << std::endl;
    return 0;
}

void mmio_close_audio(void)
{
    std::lock_guard<std::mutex> rt_lock(rt_audio_mutex);

    if (rt_audio->isStreamRunning())
        rt_audio->stopStream();

    if (rt_audio->isStreamOpen())
        rt_audio->closeStream();
}

void mmio_reportidle(void)
{
}

static inline size_t pd_input_buffer_samples()
{
    return STUFF->st_inchannels * DEFDACBLKSIZE;
}

static inline size_t pd_output_buffer_samples()
{
    return STUFF->st_outchannels * DEFDACBLKSIZE;
}

static inline void pd_output_buffer_clear()
{
    const auto out_size = pd_output_buffer_samples();
    t_sample* fbuf = STUFF->st_soundout;
    std::fill(fbuf, fbuf + out_size, 0);
}

int mmio_send_dacs(void)
{
    int rtnval = SENDDACS_YES;

    // no intput, no output
    if ((!STUFF->st_inchannels && !STUFF->st_outchannels) || !rt_audio)
        return SENDDACS_NO;

    // output
    if (STUFF->st_outchannels) {
        auto n_samples = pd_output_buffer_samples();

        while (!out_ring_buffer.write_available(n_samples)) {
            rtnval = SENDDACS_SLEPT;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // write from Pd to ring-buffer
        out_ring_buffer.write(STUFF->st_soundout, n_samples);
    }

    // input
    if (STUFF->st_inchannels) {
        auto n_samples = pd_input_buffer_samples();

        // wait for input data
        while (!input_ring_buffer.read_available(n_samples)) {
            rtnval = SENDDACS_SLEPT;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // read from ring-buffer to Pd
        input_ring_buffer.read(STUFF->st_soundin, n_samples);
    }

    pd_output_buffer_clear();
    return rtnval;
}

void mmio_getdevs(char* indevlist, int* nindevs,
    char* outdevlist, int* noutdevs, int* canmulti,
    int maxndev, int devdescsize)
{
    std::lock_guard<std::mutex> rt_lock(rt_audio_mutex);
    rt_audio_init();

    unsigned int devices = rt_audio->getDeviceCount();

    *nindevs = 0;
    *noutdevs = 0;
    // restrict to maxndev devices
    const int max_total = std::min<int>(maxndev, devices);

    for (unsigned int i = 0; i < max_total; i++) {
        RtAudio::DeviceInfo info = rt_audio->getDeviceInfo(i);
        // input device found
        if (info.inputChannels > 0) {
            // restict name to devdescsize
            const char* name = info.name.substr(0, devdescsize).c_str();
            strncpy(&indevlist[*nindevs * devdescsize], name, devdescsize - 1);
            ++(*nindevs);
        }

        // output device found
        if (info.outputChannels > 0) {
            // restict name to devdescsize
            const char* name = info.name.substr(0, devdescsize).c_str();
            strncpy(&outdevlist[*noutdevs * devdescsize], name, devdescsize - 1);
            ++(*noutdevs);
        }
    }

    *canmulti = 1;
}
