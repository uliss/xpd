#ifndef MIDIDEVICE_H
#define MIDIDEVICE_H

#include "device.h"

namespace xpd {

class MIDIDevice : public Device {
public:
    MIDIDevice(const std::string& name);
    ~MIDIDevice();
};

} // namespace xpd

#endif // MIDIDEVICE_H
