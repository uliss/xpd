#ifndef ARRAY_H
#define ARRAY_H

#include "object.h"

namespace xpd {

class Array : public Object {
public:
    Array(const Canvas* parent, const std::string& name);
};

} // namespace xpd

#endif // ARRAY_H
