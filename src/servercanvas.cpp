#include "servercanvas.h"
#include "classinfo.h"

namespace xpd {

static ClassInfoPtr canvas_class = std::make_shared<ClassInfo>("canvas");

ServerCanvas::ServerCanvas(const ServerCanvas* parent, const CanvasSettings& s)
    : Object(parent, canvas_class, s.name())
    , settings_(s)
{
}

const CanvasSettings& ServerCanvas::settings() const
{
    return settings_;
}

const std::string& ServerCanvas::path() const
{
    return path_;
}

void ServerCanvas::registerObserver(CanvasObserverPtr o)
{
}

void ServerCanvas::deleteObserver(CanvasObserverPtr o)
{
}

const ObjectList& ServerCanvas::objects() const
{
    return obj_list_;
}

bool ServerCanvas::connect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

bool ServerCanvas::disconnect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

ObjectId ServerCanvas::createObject(const std::string& name)
{
}

bool ServerCanvas::deleteObject(ObjectId objId)
{
}

ObjectId ServerCanvas::createArray(const std::string& name, size_t size)
{
}

bool ServerCanvas::deleteArray(const std::string& name)
{
}

bool ServerCanvas::hasChildren() const
{
    return true;
}

const ObjectList& ServerCanvas::children() const
{
    return obj_list_;
}

CanvasSettings::CanvasSettings(const std::string& name)
    : name_(name)
{
}

const std::string& CanvasSettings::name() const
{
    return name_;
}

} // namespace xpd
