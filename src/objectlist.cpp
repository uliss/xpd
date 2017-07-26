#include "objectlist.h"

namespace xpd {

ObjectList::ObjectList()
{
}

const ConnectionList& ObjectList::connections() const
{
    return conn_;
}

ConnectionList& ObjectList::connections()
{
    return conn_;
}

void ObjectList::push_back(const ObjectPtr& o)
{
    obj_.push_back(o);
}

} // namespace xpd
