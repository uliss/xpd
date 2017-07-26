#include "pdcanvas.h"
#include "lib_cpd.h"
#include "logger.h"
#include "pdobject.h"

using namespace xpd;

PdCanvas::PdCanvas(const Canvas* parent, const CanvasSettings& s)
    : Canvas(parent, s)
    , cnv_(0)
{
    cnv_ = cpd_root_canvas_new();
    if (!cnv_) {
        log()->error("can't create canvas");
        throw Exception("can't create canvas");
    }
}

PdCanvas::~PdCanvas()
{
    cpd_canvas_free(cnv_);
}

ObjectId PdCanvas::createObject(const std::string& name, int x, int y)
{
    if (!cnv_) {
        log()->error("canvas is NULL");
        return ObjectId(-1);
    }

    t_cpd_atomlist lst;
    lst.n = 0;
    lst.data = 0;

    ObjectPtr ptr(new PdObject(this, name));
    obj_list_.push_back(ptr);
    return ptr->id();
}

const t_cpd_canvas* PdCanvas::canvas() const
{
    return cnv_;
}
