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
    ConnectionList& connections();

    void append(Object* o);
    void clear();

    bool empty() const;
    size_t size() const;
};

} // namespace xpd

#endif // OBJECTLIST_H
