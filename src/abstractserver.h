#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <memory>
#include <vector>

#include "abstractserverprocess.h"

namespace xpd {

typedef std::vector<ProcessPtr> ProcessList;

class ServerSettings {
public:
    ServerSettings() {}
};

class AbstractServer {
    ProcessList process_list_;
    ServerSettings settings_;

public:
    AbstractServer(const ServerSettings& s);
    virtual ~AbstractServer();

    const ProcessList& instances() const { return process_list_; }
    virtual ProcessPtr createInstance() = 0;
};

} // namespace xpd

#endif // ABSTRACTSERVER_H
