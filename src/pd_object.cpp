#include "pd_object.h"
#include "pd_canvas.h"
#include "pd_localprocess.h"

#include "logger.h"

#include "cpd/cpd_object.h"
#include "cpd/cpd_types.h"

namespace xpd {

PdObject::PdObject(const Canvas* parent, const std::string& name, const PdArguments& args, int x, int y)
    : Object(parent, name, x, y)
    , cnv_(0)
    , obj_(0)
    , inlet_n_(0)
    , outlet_n_(0)
    , args_(args)
{
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

    // cache xlet number, since it should not change after object creation
    inlet_n_ = cpd_object_inlet_count(obj_);
    outlet_n_ = cpd_object_outlet_count(obj_);

    for (int i = 0; i < inlet_n_; i++) {
        XletType t = (cpd_object_inlet_type(obj_, i) == CPD_CONNECTION_SIGNAL) ? XLET_SIGNAL : XLET_MESSAGE;
        Inlet n = Inlet(t);

        inlet_list_.push_back(n);
    }

    for (int i = 0; i < outlet_n_; i++) {
        XletType t = (cpd_object_outlet_type(obj_, i) == CPD_CONNECTION_SIGNAL) ? XLET_SIGNAL : XLET_MESSAGE;
        Outlet n = Outlet(t);

        outlet_list_.push_back(n);
    }

    observer_ = 0;
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

void PdObject::setReceiveSymbol(const std::string& s)
{
    cpd_bind_object(obj_, cpd_symbol(s.c_str()));
}

void PdObject::registerObserver(ObserverPtr o)
{
    PdObjectObserver *observer = reinterpret_cast<PdObjectObserver*>(o.get());

    if (!o)
    {
        log()->error("bad observer pointer!");
        return;
    }

    observer_ = observer;
    PdLocalProcess::objectObserverMap[pdObject()] = o;

}
void PdObject::deleteObserver(ObserverPtr)
{
    observer_ = 0;
    PdLocalProcess::objectObserverMap[pdObject()] = 0;
}

} // namespace xpd

