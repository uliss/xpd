#include "abstractserver.h"

namespace xpd {

AbstractServer::AbstractServer(const ServerSettings& s)
    : settings_(s)
{
}

AbstractServer::~AbstractServer()
{
}

const ServerSettings& AbstractServer::settings() const
{
    return settings_;
}

void AbstractServer::setSettings(const ServerSettings& s)
{
    settings_ = s;
}

} // namespace xpd
