#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <memory>
#include <vector>

#include "audiodevicemanager.h"
#include "mididevicemanager.h"

namespace xpd {

class AbstractServerProcess;

typedef std::shared_ptr<AbstractServerProcess> ProcessPtr;
typedef std::vector<ProcessPtr> ProcessList;

class ServerSettings {
public:
    ServerSettings() {}
};

class AbstractServer {
    ProcessList process_list_;
    ServerSettings settings_;
    AudioDeviceManager audio_dev_;
    MIDIDeviceManager midi_dev_;

public:
    AbstractServer(const ServerSettings& s);
    virtual ~AbstractServer();

    const ProcessList& instances() const { return process_list_; }
    virtual ProcessPtr createInstance() = 0;

    const ServerSettings& settings() const;
    void setSettings(const ServerSettings& s);
};

} // namespace xpd

#endif // ABSTRACTSERVER_H
