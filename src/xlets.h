#ifndef XLETS_H
#define XLETS_H

namespace xpd {

enum XletType {
    XLET_MESSAGE = 0,
    XLET_SIGNAL
};

class Xlet {
    XletType type_;

public:
    Xlet(XletType t);
    XletType type() const;
};

class Inlet : public Xlet {
public:
    Inlet(XletType t);
};

class Outlet : public Xlet {
public:
    Outlet(XletType t);
};

} // namespace xpd

#endif // XLETS_H
