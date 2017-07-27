#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

class LocalPdServer : public AbstractServer {
public:
    LocalPdServer(const ServerSettings& s);
    ~LocalPdServer();
    ProcessPtr createProcess();
};

} // namespace xpd

#endif // LOCALSERVER_H
