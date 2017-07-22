#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include "device.h"

namespace xpd {

class AudioDevice : public Device {
public:
    AudioDevice(const std::string& name);
    ~AudioDevice();
};

} // namespace xpd

#endif // AUDIODEVICE_H
