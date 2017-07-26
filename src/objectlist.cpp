#include "objectlist.h"

namespace xpd {

ObjectList::ObjectList()
{
}

ObjectList::~ObjectList()
{
    clear();
}

const ConnectionList& ObjectList::connections() const
{
    return conn_;
}

ConnectionList& ObjectList::connections()
{
    return conn_;
}

void ObjectList::append(Object* o)
{
    obj_.push_back(o);
}

void ObjectList::clear()
{
    for (size_t i = 0; i < obj_.size(); i++)
        delete obj_[i];

    obj_.clear();
}

bool ObjectList::empty() const
{
    return obj_.empty();
}

size_t ObjectList::size() const
{
    return obj_.size();
}

} // namespace xpd
