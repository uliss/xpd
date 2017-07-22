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

} // namespace xpd
