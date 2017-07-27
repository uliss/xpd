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
    if (!checkObjectOutlet(src, srcOutletIdx))
        return false;

    if (!checkObjectInlet(dest, destInletIdx))
        return false;

    Connection c(src, srcOutletIdx, dest, destInletIdx);
    if (hasConnection(c)) {
        log()->error("ObjectList::connect: connection already exists");
        return false;
    }

    conn_.push_back(c);
    return true;
}

Object* ObjectList::findObject(ObjectId id)
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](Object* o) { return o->id() == id; });
    return it == obj_.end() ? 0 : *it;
}

const Object* ObjectList::findObject(ObjectId id) const
{
    auto it = std::find_if(obj_.begin(), obj_.end(), [id](const Object* o) { return o->id() == id; });
    return it == obj_.end() ? 0 : *it;
}

bool ObjectList::contains(ObjectId id) const
{
    return findObject(id) != 0;
}

bool ObjectList::checkObjectInlet(ObjectId id, size_t n) const
{
    const Object* obj = findObject(id);
    if (!obj) {
        log()->error("ObjectList::checkObjectInlet: object not found in list - id:{}", id);
        return false;
    }

    if (!(n < obj->inletCount())) {
        log()->error("ObjectList::checkObjectInlet: invalid inlet index - {}, max values is {}",
            n, obj->inletCount());
        return false;
    }

    return true;
}

bool ObjectList::checkObjectOutlet(ObjectId id, size_t n) const
{
    const Object* obj = findObject(id);
    if (!obj) {
        log()->error("ObjectList::checkObjectOutlet: object not found in list - id:{}", id);
        return false;
    }

    if (!(n < obj->outletCount())) {
        log()->error("ObjectList::checkObjectOutlet: invalid outlet index - {}, max values is {}",
            n, obj->outletCount());
        return false;
    }

    return true;
}

bool ObjectList::hasConnection(const Connection& c) const
{
    return std::find(conn_.begin(), conn_.end(), c) != conn_.end();
}

} // namespace xpd
