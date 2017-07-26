#include "array.h"
#include "classinfo.h"

namespace xpd {

static ClassInfoPtr array_class = std::make_shared<ClassInfo>("array");

Array::Array(const Canvas* parent, const std::string& name)
    : Object(parent, name)
{
}

} // namespace xpd
