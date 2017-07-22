#include "servercanvas.h"

namespace xpd {

ServerCanvas::ServerCanvas(const CanvasSettings& s)
    : settings_(s)
{
}

const CanvasSettings& ServerCanvas::settings() const
{
    return settings_;
}

} // namespace xpd
