#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include "device.h"

namespace xpd {

class VideoDevice : public Device {
public:
    VideoDevice(const std::string& name);
};

} // namespace xpd

#endif // VIDEODEVICE_H
