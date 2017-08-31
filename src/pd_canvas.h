#ifndef PDCANVAS_H
#define PDCANVAS_H

#include "canvas.h"
#include "cpd/cpd_canvas.h"

namespace xpd {

class PdCatcher;

class PdCanvas : public Canvas {
    t_cpd_canvas* cnv_;
    PdCanvas();
    PdCanvas(const PdCanvas&);
    void operator=(const PdCanvas&);

public:
    PdCanvas(const CanvasSettings& s);
    ~PdCanvas();

    ObjectId createObject(const std::string& name, int x, int y) override;

    virtual bool connect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx) override;
    virtual bool disconnect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx) override;

    const t_cpd_canvas* canvas() const;

    /**
     * Creates new array on canvas
     * @param name - array name
     * @param size - array size
     * @return array ID
     */
    ObjectId createArray(const std::string& name, size_t size) override;

    void loadbang() override;

    std::vector<std::string> availableObjects() const override;

public:
    friend class PdCatcher;

private:
    PdCanvas(const Canvas* parent, const CanvasSettings& s);
    t_cpd_object* findById(ObjectId id);
    void updateXlets();
    void updateInlets();
    void updateOutlets();
};

} // namespace xpd

#endif // PDCANVAS_H
