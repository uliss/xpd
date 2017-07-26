#include "servercanvas.h"

#include <algorithm>

namespace xpd {

Canvas::Canvas(const Canvas* parent, const CanvasSettings& s)
    : Object(parent, s.name())
    , settings_(s)
{
}

const CanvasSettings& Canvas::settings() const
{
    return settings_;
}

const std::string& Canvas::path() const
{
    return path_;
}

void Canvas::registerObserver(CanvasObserverPtr o)
{
}

void Canvas::deleteObserver(CanvasObserverPtr o)
{
}

const ObjectList& Canvas::objects() const
{
    return obj_list_;
}

bool Canvas::connect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

bool Canvas::disconnect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

bool Canvas::deleteObject(ObjectId objId)
{
}

ObjectId Canvas::createArray(const std::string& name, size_t size)
{
}

bool Canvas::deleteArray(const std::string& name)
{
}

bool Canvas::hasChildren() const
{
    return !obj_list_.empty();
}

size_t Canvas::childrenCount() const
{
    return obj_list_.size();
}

const ObjectList& Canvas::children() const
{
    return obj_list_;
}

ObjectType Canvas::type() const
{
    return OBJ_TYPE_CANVAS;
}

CanvasSettings::CanvasSettings(const std::string& name, int x, int y, size_t w, size_t h)
    : name_(name)
    , x_(std::max(0, x))
    , y_(std::max(0, y))
    , w_(w)
    , h_(h)
{
}

const std::string& CanvasSettings::name() const
{
    return name_;
}

} // namespace xpd
