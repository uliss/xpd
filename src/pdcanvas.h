#ifndef PDCANVAS_H
#define PDCANVAS_H

#include "m_pd.h"

#include "servercanvas.h"

namespace xpd {

class PdCanvas : public Canvas {
    t_canvas* cnv_;

public:
    PdCanvas(const Canvas* parent, const CanvasSettings& s);
};

} // namespace xpd

#endif // PDCANVAS_H
