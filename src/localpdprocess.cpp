#include "localpdprocess.h"

namespace xpd {

LocalPdProcess::LocalPdProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
}

void LocalPdProcess::dspSwitch(bool value)
{
}

} // namespace xpd
