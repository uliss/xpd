#include "objectlist.h"
#include "logger.h"

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

bool ObjectList::append(Object* o)
{
    if (!o)
        return false;

    // check if already exists
    auto it = std::find(obj_.begin(), obj_.end(), o);
    if (it != obj_.end()) {
        log()->error("ObjectList::append: double insertion attempt ({})", static_cast<void*>(o));
        return false;
    }

    obj_.push_back(o);
    return true;
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

bool ObjectList::connect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx)
{
    return false;
}

Object* ObjectList::findObject(ObjectId id)
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](Object* o) { return o->id() == id; });
    return it == obj_.end() ? 0 : *it;
}

bool ObjectList::contains(ObjectId id)
{
    return findObject(id) != 0;
}

} // namespace xpd
