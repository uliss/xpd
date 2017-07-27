#ifndef LOCALPDPROCESS_H
#define LOCALPDPROCESS_H

#include "abstractserverprocess.h"

namespace xpd {

class PdLocalProcess : public AbstractServerProcess {
public:
    PdLocalProcess(const AbstractServer* parent, const ServerProcessSettings& s);
    ~PdLocalProcess();

    void dspSwitch(bool value);

    /**
     * Creates PdCanvas
     * @return pointer to new canvas or 0 on error
     */
    CanvasPtr createCanvas();
};

} // namespace xpd

#endif // LOCALPDPROCESS_H
