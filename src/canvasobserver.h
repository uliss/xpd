#ifndef CANVASOBSERVER_H
#define CANVASOBSERVER_H

#include "observer.h"

namespace xpd {

class CanvasObserver : public Observer {
public:
    CanvasObserver();
    
    virtual void inletAdded();
    virtual void inletRemoved();

    virtual void outletAdded();
    virtual void outletRemoved();
};

} // namespace xpd

#endif // CANVASOBSERVER_H
