#include "localserver.h"
#include "localpdprocess.h"

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

    ProcessPtr ptr;

    try {
        ServerProcessSettings s;
        ptr = std::make_shared<LocalPdProcess>(this, s);

        if (!ptr)
            return ptr;

    } catch (std::exception& e) {
        std::cerr << "LocalPdProcess crashed: " << e.what() << std::endl;
        return ProcessPtr();
    }

    process_list_.push_back(ptr);
    return process_list_.front();
}

} // namespace xpd
