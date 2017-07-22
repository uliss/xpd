#ifndef DEVICE_H
#define DEVICE_H

#include <string>

namespace xpd {
class Device {
protected:
    std::string name_;

public:
    Device(const std::string& name);
    virtual ~Device();

    virtual const std::string& name() const;
};
}

#endif // DEVICE_H
