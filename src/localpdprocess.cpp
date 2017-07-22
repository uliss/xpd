#include "localpdprocess.h"
#include "lib_cmp.h"

namespace xpd {

LocalPdProcess::LocalPdProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
    if (!cmp_pdinit())
        throw Exception("can't start pd");
}

void LocalPdProcess::dspSwitch(bool value)
{
}

} // namespace xpd
