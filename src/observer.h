#ifndef OBSERVER_H
#define OBSERVER_H

namespace xpd {

class Observer {
public:
    Observer();
    virtual ~Observer();

    virtual void update();
};

} // namespace xpd

#endif // OBSERVER_H
