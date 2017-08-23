#include "objectobserver.h"

namespace xpd {

ObjectObserver::ObjectObserver()
{
    _data = 0;
}

ObjectObserver::~ObjectObserver()
{
}

void ObjectObserver::update()
{
}

void ObjectObserver::setData(t_cpd_list* data)
{
    _data = data;
}
t_cpd_list* ObjectObserver::data()
{
    return _data;
}

} // namespace xpd
