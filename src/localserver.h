#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include "abstractserver.h"

namespace xpd {

class LocalServer : public AbstractServer {
public:
    LocalServer(const ServerSettings& s);
};

} // namespace xpd

#endif // LOCALSERVER_H
