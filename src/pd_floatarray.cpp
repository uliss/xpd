#include "pd_floatarray.h"
#include "classinfo.h"

namespace xpd {

static ClassInfoPtr PdFloatArray_class = std::make_shared<ClassInfo>("PdFloatArray");

PdFloatArray::PdFloatArray(const Canvas* parent, const std::string& name, size_t size)
    : Object(parent, name)
{
}

int PdFloatArray::size()
{
}
    
void PdFloatArray::setSize(int size)
{
}

PdFloatArrayData* PdFloatArray::getData()
{
}

void PdFloatArray::registerObserver(Observer* o)
{
}
    
void PdFloatArray::unregisterObserver(Observer* o)
{
}

} // namespace xpd
