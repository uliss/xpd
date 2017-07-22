#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "audiodevicemanager.h"
#include "mididevicemanager.h"

namespace xpd {

class AbstractServerProcess;

typedef std::shared_ptr<AbstractServerProcess> ProcessPtr;
typedef std::vector<ProcessPtr> ProcessList;

class ServerSettings {
    std::string name_;

public:
    explicit ServerSettings(const std::string& name)
        : name_(name)
    {
    }

    const std::string& name() const;

    bool operator==(const ServerSettings& s);
    bool operator!=(const ServerSettings& s);
};

class AbstractServer {
protected:
    ProcessList process_list_;
    ServerSettings settings_;
    AudioDeviceManager audio_dev_;
    MIDIDeviceManager midi_dev_;

public:
    typedef std::runtime_error Exception;

public:
    AbstractServer(const ServerSettings& s);
    virtual ~AbstractServer();

    const ServerSettings& settings() const;
    void setSettings(const ServerSettings& s);

    const ProcessList& processList() const;

    /**
     * @brief creates new process
     * @return pointer to new process or null-ptr on error
     */
    virtual ProcessPtr createProcess() = 0;

    /**
     * Returns server name 
     */
    const std::string& name() const;
};

} // namespace xpd

#endif // ABSTRACTSERVER_H
