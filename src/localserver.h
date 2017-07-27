#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

class PdLocalServer : public AbstractServer {
public:
    PdLocalServer(const ServerSettings& s);
    ~PdLocalServer();
    ProcessPtr createProcess();
};

} // namespace xpd

#endif // LOCALSERVER_H
