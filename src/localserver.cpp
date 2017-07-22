#include "localserver.h"

namespace xpd {

LocalServer::LocalServer(const ServerSettings& s)
    : AbstractServer(s)
{
}

LocalPdServer::LocalPdServer(const ServerSettings& s)
    : LocalServer(s)
{
}

ProcessPtr LocalPdServer::createProcess()
{
    if (process_list_.size() > 0)
        return process_list_.front();

    ProcessPtr p;
    process_list_.push_back(p);
    return process_list_.front();
}

} // namespace xpd
