#include "pdobject.h"
#include "logger.h"
#include "pdcanvas.h"

namespace xpd {

PdObject::PdObject(const Canvas* parent, const std::string& name, int x, int y)
    : Object(parent, name, x, y)
    , cnv_(0)
    , obj_(0)
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
}

PdObject::~PdObject()
{
}

} // namespace xpd
