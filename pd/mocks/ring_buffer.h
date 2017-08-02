#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstddef>

#include "s_audio_paring.h"

template <size_t N>
class RingBuffer {
    float data_[N];
    sys_ringbuf ring_buf_;

public:
    RingBuffer(int pos = 0)
    {
        sys_ringbuf_init(&ring_buf_, N, (char*)data_, pos);
    }

    size_t size() const { return N; }

    void write(const float* from, size_t n)
    {
        sys_ringbuf_write(&ring_buf_, from, n * sizeof(float), (char*)data_);
    }

    void read(float* to, size_t n)
    {
        sys_ringbuf_read(&ring_buf_, to, n * sizeof(float), (char*)data_);
    }

    bool read_available(size_t n)
    {
        return sys_ringbuf_getreadavailable(&ring_buf_) >= (n * sizeof(float));
    }

    bool write_available(size_t n)
    {
        return sys_ringbuf_getwriteavailable(&ring_buf_) >= (n * sizeof(float));
    }
};

#endif // RING_BUFFER_H
