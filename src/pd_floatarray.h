#ifndef PdFloatArray_H
#define PdFloatArray_H

#include "array.h"
#include "pd_floatarraydata.h"

#include "cpd/cpd_types.h"

namespace xpd {

class PdFloatArray : public FloatArray {
    t_cpd_canvas* cnv_;
    t_cpd_array* arr_;
    Observer* _observer;

public:
    PdFloatArray(const Canvas* parent, const std::string& name, size_t size);
    ~PdFloatArray();

    PdFloatArrayData* getData();

    float at(size_t idx) const;
    bool resize(size_t sz);
    void setPlotStyle(PlotStyle style);
    void fill(float v);
};

} // namespace xpd

#endif // PdFloatArray_H
