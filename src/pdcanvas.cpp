#include "pdcanvas.h"
#include "lib_cpd.h"

using namespace xpd;

PdCanvas::PdCanvas(const Canvas* parent, const CanvasSettings& s)
    : Canvas(parent, s)
    , cnv_(0)
{
    cnv_ = cpd_new_patch(s.x(), s.y(), s.width(), s.height(), 10);
}
