#include "abstractserverprocess.h"

#include <algorithm>
#include <iostream>

using namespace xpd;

AbstractServerProcess::AbstractServerProcess(const AbstractServer* parent,
    const ServerProcessSettings& s)
    : settings_(s)
    , parent_(parent)
    , log_level_(LOG_DEBUG)
{
    console_observer_ = 0;
}

AbstractServerProcess::~AbstractServerProcess()
{
}

const ServerProcessSettings& AbstractServerProcess::settings() const
{
    return settings_;
}

void AbstractServerProcess::setSettings(const ServerProcessSettings& s)
{
    settings_ = s;
}

const ServerPath& AbstractServerProcess::path() const
{
    return path_;
}

ServerPath& AbstractServerProcess::path()
{
    return path_;
}

void AbstractServerProcess::registerObserver(ObserverPtr o)
{
}

void AbstractServerProcess::unregisterObserver(ObserverPtr o)
{
}

void AbstractServerProcess::addSearchPath(const std::string& path)
{
}

bool AbstractServerProcess::loadLibrary(const std::string& libraryName)
{
}

bool AbstractServerProcess::loadExternal(const std::string& externalName)
{
}

const AbstractServer* AbstractServerProcess::parent() const
{
    return parent_;
}

void AbstractServerProcess::post(const std::string& text)
{
    std::cout << text << std::endl;
}

void AbstractServerProcess::error(const std::string& text)
{
    std::cerr << "[error] " << text << std::endl;
}

void AbstractServerProcess::log(LogLevel level, const std::string& text)
{
}

LogLevel AbstractServerProcess::logLevel() const
{
    return log_level_;
}

void AbstractServerProcess::setLogLevel(LogLevel l)
{
    log_level_ = l;
}

bool AbstractServerProcess::deleteCanvas(CanvasPtr cnv)
{
    auto it = std::find(canvas_list_.begin(), canvas_list_.end(), cnv);
    if (it == canvas_list_.end())
        return false;

    canvas_list_.erase(it);
    return true;
}

const CanvasList& AbstractServerProcess::canvasList() const
{
    return canvas_list_;
}

size_t AbstractServerProcess::canvasCount() const
{
    return canvas_list_.size();
}

LibraryList AbstractServerProcess::loadedLibraries() const
{
}

ClassList AbstractServerProcess::loadedClasses() const
{
}

void AbstractServerProcess::sendMessage(const std::string& object, const std::string& text)
{
}

void AbstractServerProcess::registerConsoleObserver(ConsoleObserverPtr o)
{
    console_observer_ = o;
}

void AbstractServerProcess::unregisterConsoleObserver(ConsoleObserverPtr o)
{
    console_observer_ = 0;
}
