#include "localserver.h"
#include "localpdprocess.h"
#include "logger.h"

namespace xpd {

LocalServer::LocalServer(const ServerSettings& s)
    : AbstractServer(s)
{
}

LocalPdServer::LocalPdServer(const ServerSettings& s)
    : LocalServer(s)
{
}

LocalPdServer::~LocalPdServer()
{
}

ProcessPtr LocalPdServer::createProcess()
{
    if (process_list_.size() > 0)
        return process_list_.front();

    ProcessPtr ptr;

    try {
        ServerProcessSettings s;
        ptr = std::make_shared<LocalPdProcess>(this, s);

        if (!ptr)
            return ptr;

    } catch (std::exception& e) {
        log()->critical("LocalPdProcess crashed: {}", e.what());
        return ProcessPtr();
    }

    process_list_.push_back(ptr);
    return process_list_.front();
}

} // namespace xpd
