#include "servercanvas.h"

namespace xpd {

ServerCanvas::ServerCanvas(const CanvasSettings& s)
    : settings_(s)
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

int ServerCanvas::inletCount() const
{
}

int ServerCanvas::outletCount() const
{
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

const ConnectionList& ServerCanvas::connections() const
{
    return conn_list_;
}

bool ServerCanvas::connect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

bool ServerCanvas::disconnect(const Object& src, int outletIdx, const Object& dest, int inletIdx)
{
    return false;
}

} // namespace xpd
