#ifndef PDOBJECT_H
#define PDOBJECT_H

#include "lib_cpd.h"
#include "object.h"

namespace xpd {

class PdObject : public Object {
    t_cpd_canvas* cnv_;
    t_cpd_object* obj_;
    size_t inlet_n_;
    size_t outlet_n_;

public:
    PdObject(const Canvas* parent, const std::string& name, int x = 0, int y = 0);
    ~PdObject();

    void setX(int x);
    void setY(int y);

    size_t inletCount() const;
    size_t outletCount() const;
};

} // namespace xpd

#endif // PDOBJECT_H
