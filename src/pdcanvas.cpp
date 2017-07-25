#include "pdcanvas.h"
#include "lib_cpd.h"
#include "logger.h"

using namespace xpd;

PdCanvas::PdCanvas(const Canvas* parent, const CanvasSettings& s)
    : Canvas(parent, s)
    , cnv_(0)
{
    cnv_ = cpd_root_canvas_new();
    if (!cnv_) {
        log()->error("can't create canvas");
    }
}

PdCanvas::~PdCanvas()
{
    cpd_canvas_free(cnv_);
}
