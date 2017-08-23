#include "array.h"
#include "classinfo.h"

namespace xpd {

static ClassInfoPtr array_class = std::make_shared<ClassInfo>("array");

Array::Array(const Canvas* parent, const std::string& name, size_t size)
    : Object(parent, name)
{
}

int Array::size()
{
}
    
void Array::setSize(int size)
{
}

ArrayData* Array::getData()
{
}

void Array::registerObserver(Observer* o)
{
}
    
void Array::unregisterObserver(Observer* o)
{
}

} // namespace xpd
