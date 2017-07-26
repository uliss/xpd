#include "pdobject.h"
#include "logger.h"
#include "pdcanvas.h"

namespace xpd {

PdObject::PdObject(const Canvas* parent, const std::string& name, int x, int y)
    : Object(parent, name, x, y)
    , cnv_(0)
    , obj_(0)
    , inlet_n_(0)
    , outlet_n_(0)
{
    static size_t id_counter_ = 2000;

    const PdCanvas* pd_canvas = dynamic_cast<const PdCanvas*>(parent);
    if (!pd_canvas) {
        throw Exception("PdObject: invalid canvas pointer given. PdCanvas* expected");
    }

    cnv_ = const_cast<t_cpd_canvas*>(pd_canvas->canvas());
    if (!cnv_) {
        throw Exception("PdObject: NULL canvas pointer");
    }

    obj_ = cpd_object_new(cnv_, name.c_str(), 0, x, y);
    if (!obj_) {
        throw Exception("PdObject: can't create object");
    }

    id_ = id_counter_++;

    inlet_n_ = cpd_object_inlet_count(obj_);
    outlet_n_ = cpd_object_outlet_count(obj_);
}

PdObject::~PdObject()
{
    cpd_object_free(cnv_, obj_);
}

void PdObject::setX(int x)
{
    Object::setX(x);
    cpd_object_set_xpos(obj_, x);
}

void PdObject::setY(int y)
{
    Object::setY(y);
    cpd_object_set_ypos(obj_, y);
}

size_t PdObject::inletCount() const
{
    return inlet_n_;
}

size_t PdObject::outletCount() const
{
    return outlet_n_;
}

} // namespace xpd
