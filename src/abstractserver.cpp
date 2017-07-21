#include "abstractserver.h"

namespace xpd {

AbstractServer::AbstractServer(const ServerSettings& s)
    : settings_(s)
{
}

AbstractServer::~AbstractServer()
{
}

} // namespace xpd
