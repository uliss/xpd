#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

class LocalServer : public AbstractServer {
public:
    LocalServer(const ServerSettings& s);
};

class LocalPdServer : public LocalServer {
public:
    LocalPdServer(const ServerSettings& s);
    ProcessPtr createProcess();
};

} // namespace xpd

#endif // LOCALSERVER_H
