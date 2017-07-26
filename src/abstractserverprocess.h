#ifndef ABSTRACTSERVERPROCESS_H
#define ABSTRACTSERVERPROCESS_H

#include <memory>
#include <stdexcept>
#include <vector>

#include "classinfo.h"
#include "consoleobserver.h"
#include "libraryinfo.h"
#include "observer.h"
#include "servercanvas.h"
#include "serverpath.h"

namespace xpd {

class ServerProcessSettings {
public:
    ServerProcessSettings() {}
};

typedef std::shared_ptr<Canvas> CanvasPtr;
typedef std::vector<CanvasPtr> CanvasList;

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
private:
    AbstractServerProcess();
    AbstractServerProcess(const AbstractServerProcess&);

protected:
    ServerProcessSettings settings_;
    CanvasList canvas_list_;
    ObserverList observer_list_;
    ServerPath path_;
    ConsoleObserverPtr console_observer_;
    const AbstractServer* parent_;
    LogLevel log_level_;

public:
    typedef std::runtime_error Exception;

public:
    AbstractServerProcess(const AbstractServer* parent, const ServerProcessSettings& s);
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

    virtual void post(const std::string& text = "");
    virtual void error(const std::string& text = "");
    virtual void log(LogLevel level, const std::string& text);

    LogLevel logLevel() const;
    void setLogLevel(LogLevel l);

    virtual CanvasPtr createCanvas() = 0;
    virtual bool deleteCanvas(CanvasPtr cnv);
    const CanvasList& canvasList() const;
    virtual size_t canvasCount() const;

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
