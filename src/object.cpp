#include "object.h"
#include "propertyobserver.h"

namespace xpd {

Object::Object(const ServerCanvas* parent, ClassInfoPtr c, const std::string& name)
    : parent_(parent)
    , name_(name)
    , class_(c)
    , id_(0)
{
}

Object::~Object()
{
}

const std::string& Object::name() const
{
    return name_;
}

const ServerCanvas* Object::parent() const
{
    return parent_;
}

size_t Object::inletCount() const
{
    return 0;
}

size_t Object::outletCount() const
{
    return 0;
}

ObjectType Object::type() const
{
    return OBJ_TYPE_SIMPLE_BOX;
}

void Object::setType(ObjectType type)
{
}

void Object::registerObserver(ObserverPtr o)
{
}

void Object::deleteObserver(ObserverPtr)
{
}

const InletList& Object::inlets() const
{
    return inlet_list_;
}

const OutletList& Object::outlets() const
{
    return outlet_list_;
}

const ObjectProperties& Object::properties() const
{
    static ObjectProperties props;
    return props;
}

ObjectId Object::id() const
{
    return id_;
}

} // namespace xpd
