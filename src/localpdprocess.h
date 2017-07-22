#ifndef LOCALPDPROCESS_H
#define LOCALPDPROCESS_H

#include "abstractserverprocess.h"

namespace xpd {

class LocalPdProcess : public AbstractServerProcess {
public:
    LocalPdProcess(const AbstractServer* parent, const ServerProcessSettings& s);

    void dspSwitch(bool value);
};

} // namespace xpd

#endif // LOCALPDPROCESS_H
