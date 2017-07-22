#include "abstractserverprocess.h"

#include <iostream>

using namespace xpd;

AbstractServerProcess::AbstractServerProcess(AbstractServer* parent, const ServerProcessSettings& s)
    : settings_(s)
    , parent_(parent)
    , log_level_(LOG_DEBUG)
{
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

Logger& AbstractServerProcess::post(const std::string& text)
{
    std::cout << text << std::endl;
}

Logger& AbstractServerProcess::error(const std::string& text)
{
    std::cerr << "[error] " << text << std::endl;
}

Logger& AbstractServerProcess::log(LogLevel level, const std::string& text)
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

ServerCanvasPtr AbstractServerProcess::createCanvas()
{
}

bool AbstractServerProcess::deleteCanvas(ServerCanvasPtr cnv)
{
}

const ServerCanvasList& AbstractServerProcess::canvasList() const
{
    return canvas_list_;
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
