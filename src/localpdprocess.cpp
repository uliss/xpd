#include "localpdprocess.h"
#include "lib_cpd.h"

namespace xpd {

LocalPdProcess::LocalPdProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
    if (!cpd_init())
        throw Exception("can't start pd");
}

void LocalPdProcess::dspSwitch(bool value)
{
}

} // namespace xpd
