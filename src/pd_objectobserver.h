#ifndef OBJECT_OBSERVER_H
#define OBJECT_OBSERVER_H

#include "observer.h"
#include "cpd/cpd_list.h"

namespace xpd {

class PdObjectObserver : public Observer {
    t_cpd_list* _data;

public:
    PdObjectObserver();
    virtual ~PdObjectObserver();

    virtual void update();

    void setData(t_cpd_list* data);
    t_cpd_list* data();
};

} // namespace xpd

#endif // OBSERVER_H
