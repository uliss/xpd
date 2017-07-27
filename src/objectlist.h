#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include "connection.h"
#include "object.h"

#include <vector>

namespace xpd {

typedef std::vector<Connection> ConnectionList;

class ObjectList {
    std::vector<Object*> obj_;
    ConnectionList conn_;

public:
    ObjectList();
    ~ObjectList();

    const std::vector<Object*>& get() const { return obj_; }
    std::vector<Object*>& get() { return obj_; }

    const ConnectionList& connections() const;

    /**
     * Appends object to object list
     * @return true on success, false on error
     */
    bool append(Object* o);
    void clear();
    bool remove(ObjectId id);

    bool empty() const;
    size_t size() const;

    bool connect(ObjectId src, size_t srcOutletIdx, ObjectId dest, size_t destInletIdx);

    Object* findObject(ObjectId id);
    bool contains(ObjectId id);
};

} // namespace xpd

#endif // OBJECTLIST_H
