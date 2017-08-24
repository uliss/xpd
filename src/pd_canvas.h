#ifndef PDCANVAS_H
#define PDCANVAS_H

#include "canvas.h"
#include "cpd/cpd_canvas.h"

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

    bool connect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx);

    const t_cpd_canvas* canvas() const;
    
    ObjectId createArray(const std::string& name, size_t size);
    bool deleteArray(const std::string& name);
    
    void loadbang();

private:
    t_cpd_object* findById(ObjectId id);
};

} // namespace xpd

#endif // PDCANVAS_H
