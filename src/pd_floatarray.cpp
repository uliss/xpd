#include "pd_floatarray.h"
#include "logger.h"
#include "pd_canvas.h"

#include "cpd/cpd_array.h"
#include "cpd/cpd_object.h"

namespace xpd {

//static ClassInfoPtr PdFloatArray_class = std::make_shared<ClassInfo>("PdFloatArray");

PdFloatArray::PdFloatArray(const Canvas* parent, const std::string& name, size_t size)
    : FloatArray(parent, name, size)
    , cnv_(nullptr)
    , arr_(nullptr)
{
    const PdCanvas* pd_canvas = dynamic_cast<const PdCanvas*>(parent);
    if (!pd_canvas) {
        throw Exception("PdFloatArray: invalid canvas pointer given. PdCanvas* expected");
    }

    cnv_ = const_cast<t_cpd_canvas*>(pd_canvas->canvas());
    if (!cnv_) {
        throw Exception("PdFloatArray: NULL canvas pointer");
    }

    arr_ = cpd_array_new(cnv_, cpd_symbol(name.c_str()), size, 0);
    if (!arr_) {
        throw Exception("can't create array");
    }
}

PdFloatArray::~PdFloatArray()
{
    cpd_array_free(cnv_, arr_);
}

PdFloatArrayData* PdFloatArray::getData()
{
    return 0;
}

float PdFloatArray::at(size_t idx) const
{
    if (idx >= size())
        throw Exception(fmt::format("invalid index: {}", idx));

    return cpd_array_float_at(arr_, idx);
}

bool PdFloatArray::resize(size_t sz)
{
    if (cpd_array_resize(arr_, sz)) {
        size_ = sz;
        return true;
    }

    return false;
}

} // namespace xpd
