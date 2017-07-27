#ifndef PDCANVAS_H
#define PDCANVAS_H

#include "canvas.h"
#include "lib_cpd.h"

namespace xpd {

class PdCanvas : public Canvas {
    t_cpd_canvas* cnv_;
    PdCanvas();
    PdCanvas(const PdCanvas&);
    void operator=(const PdCanvas&);

public:
    PdCanvas(const Canvas* parent, const CanvasSettings& s);
    ~PdCanvas();

    ObjectId createObject(const std::string& name, int x, int y);

    const t_cpd_canvas* canvas() const;
};

} // namespace xpd

#endif // PDCANVAS_H
