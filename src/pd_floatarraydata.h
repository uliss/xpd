#ifndef PD_FLOATARRAYDATA_H
#define PD_FLOATARRAYDATA_H

namespace xpd {

typedef struct _PdFloatArrayData {
    int size;
    float* sample;
} PdFloatArrayData;

} // namespace xpd

#endif // ARRAYDATA_H
