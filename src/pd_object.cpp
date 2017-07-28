#include "pd_object.h"
#include "logger.h"
#include "pd_canvas.h"

#include "cpd/cpd_object.h"

namespace xpd {

PdObject::PdObject(const Canvas* parent, const std::string& name, const PdArguments& args, int x, int y)
    : Object(parent, name, x, y)
    , cnv_(0)
    , obj_(0)
    , inlet_n_(0)
    , outlet_n_(0)
    , args_(args)
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

    obj_ = cpd_object_new(cnv_, name.c_str(), args.atomList(), x, y);
    if (!obj_) {
        throw Exception("PdObject: can't create object");
    }

    id_ = id_counter_++;

    // cache xlet number, since it should not change after object creation
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

const Arguments& PdObject::arguments() const
{
    return args_;
}

t_cpd_object* PdObject::pdObject()
{
    return obj_;
}

void PdObject::sendBang()
{
    cpd_send_bang(obj_);
}

void PdObject::sendFloat(float f)
{
    cpd_send_float(obj_, f);
}

void PdObject::sendSymbol(const std::string& s)
{
}

} // namespace xpd
