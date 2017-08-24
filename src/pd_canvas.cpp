#include "pd_canvas.h"
#include "logger.h"
#include "pd_object.h"

#include "cpd/cpd.h"

using namespace xpd;

PdCanvas::PdCanvas(const Canvas* parent, const CanvasSettings& s)
    : Canvas(parent, s)
    , cnv_(0)
{
    cnv_ = cpd_patch_new();
    if (!cnv_) {
        log()->error("can't create canvas");
        throw Exception("can't create canvas");
    }
}

PdCanvas::~PdCanvas()
{
    obj_list_.clear();
    cpd_canvas_free(cnv_);
}

ObjectId PdCanvas::createObject(const std::string& name, int x, int y)
{
    if (!cnv_) {
        log()->error("canvas is NULL");
        return ObjectId(-1);
    }

    //    t_cpd_atomlist* lst = cpd_list_new();
    //    lst.n = 0;
    //    lst.data = 0;

    Object* obj = new PdObject(this, name, PdArguments(), x, y);
    obj_list_.append(obj);
    return obj->id();
}

bool PdCanvas::connect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx)
{
    t_cpd_object* pd_src = findById(src);
    t_cpd_object* pd_dest = findById(dest);

    if (!pd_src || !pd_dest) {
        log()->error("PdCanvas::connect: invalid object ID: {} {}", src, dest);
        return false;
    }

    if (!obj_list_.connect(src, outletIdx, dest, inletIdx))
        return false;

    return cpd_connect(pd_src, outletIdx, pd_dest, inletIdx);
}

const t_cpd_canvas* PdCanvas::canvas() const
{
    return cnv_;
}

t_cpd_object* PdCanvas::findById(ObjectId id)
{
    Object* o = obj_list_.findObject(id);
    return o ? static_cast<PdObject*>(o)->pdObject() : nullptr;
}

ObjectId PdCanvas::createArray(const std::string& name, size_t size)
{
    return 0;
}

bool PdCanvas::deleteArray(const std::string& name)
{
    return false;
}

void PdCanvas::loadbang()
{
    cpd_canvas_loadbang(cnv_);
}
