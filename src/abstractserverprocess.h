#ifndef ABSTRACTSERVERPROCESS_H
#define ABSTRACTSERVERPROCESS_H

#include <memory>
#include <vector>

#include "classinfo.h"
#include "consoleobserver.h"
#include "libraryinfo.h"
#include "logger.h"
#include "observer.h"
#include "servercanvas.h"
#include "serverpath.h"

namespace xpd {

class ServerProcessSettings {
public:
    ServerProcessSettings() {}
};

typedef std::unique_ptr<ServerCanvas> ServerCanvasPtr;
typedef std::vector<ServerCanvasPtr> ServerCanvasList;

typedef std::shared_ptr<ConsoleObserver> ConsoleObserverPtr;
typedef std::shared_ptr<Observer> ObserverPtr;
typedef std::vector<ObserverPtr> ObserverList;

typedef std::vector<LibraryInfo> LibraryList;
typedef std::vector<ClassInfo> ClassList;

class AbstractServer;

enum LogLevel {
    LOG_ERROR,
    LOG_FATAL,
    LOG_INFO,
    LOG_DEBUG,
    LOG_DUMP
};

class AbstractServerProcess {
    ServerProcessSettings settings_;
    ServerCanvasList canvas_list_;
    ObserverList observer_list_;
    ServerPath path_;
    ConsoleObserverPtr console_observer_;
    const AbstractServer* parent_;
    LogLevel log_level_;

public:
    AbstractServerProcess(AbstractServer* parent, const ServerProcessSettings& s);
    virtual ~AbstractServerProcess();

    void dspOn() { dspSwitch(true); }
    void dspOff() { dspSwitch(false); }
    virtual void dspSwitch(bool value) = 0;

    const ServerProcessSettings& settings() const;
    void setSettings(const ServerProcessSettings& s);

    const ServerPath& path() const;
    ServerPath& path();

    void registerObserver(ObserverPtr o);
    void unregisterObserver(ObserverPtr o);

    // ?
    void registerConsoleObserver(ConsoleObserverPtr o);

    void addSearchPath(const std::string& path);

    bool loadLibrary(const std::string& libraryName);
    bool loadExternal(const std::string& externalName);

    const AbstractServer* parent() const;

    virtual Logger& post(const std::string& text = "");
    virtual Logger& error(const std::string& text = "");
    virtual Logger& log(LogLevel level, const std::string& text);

    LogLevel logLevel() const;
    void setLogLevel(LogLevel l);

    virtual ServerCanvasPtr createCanvas();
    virtual bool deleteCanvas(ServerCanvasPtr cnv);
    const ServerCanvasList& canvasList() const;

    virtual LibraryList loadedLibraries() const;
    virtual ClassList loadedClasses() const;

    virtual void sendMessage(const std::string& object, const std::string& text);
};
}

//class PDSERVER_EXPORT ServerInstance // : Object ??
//{
//    static string getBindObjectsList();
//    static string getAudioAPIs();
//};

#endif // ABSTRACTSERVERPROCESS_H
