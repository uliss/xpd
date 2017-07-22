#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include "connection.h"
#include "object.h"

#include <vector>

namespace xpd {

typedef std::vector<Connection> ConnectionList;

class ObjectList {
    std::vector<ObjectPtr> obj_;
    ConnectionList conn_;

public:
    ObjectList();

    const std::vector<ObjectPtr>& get() const { return obj_; }
    std::vector<ObjectPtr>& get() { return obj_; }

    const ConnectionList& connections() const;
    ConnectionList& connections();
};

} // namespace xpd

#endif // OBJECTLIST_H
