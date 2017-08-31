#include "pd_localprocess.h"
#include "cpd/cpd.h"
#include "pd_canvas.h"
#include "pd_consoleobserver.h"

namespace xpd {

PdLocalProcess::PdLocalProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
    if (!cpd_init())
        throw Exception("can't start pd");
}

PdLocalProcess::~PdLocalProcess()
{
    cpd_stop();
}

void PdLocalProcess::dspSwitch(bool value)
{
    cpd_dsp_switch(value);
}

CanvasPtr PdLocalProcess::createCanvas()
{
    CanvasSettings s("Untitled-1");
    CanvasPtr cnv = std::make_shared<PdCanvas>(s);

    if (!cnv)
        return cnv;

    canvas_list_.push_back(cnv);
    return cnv;
}

void PdLocalProcess::post(const std::string& text)
{
    if (console_observer_) {
        console_observer_->setText(text);
        console_observer_->update();
    }
}

void PdLocalProcess::error(const std::string& text)
{
}

void PdLocalProcess::log(LogLevel level, const std::string& text)
{
}

void PdLocalProcess::setLogLevel(LogLevel l)
{
    this->AbstractServerProcess::setLogLevel(l);

    cpd_set_verbose_level((int)l);
}

void PdLocalProcess::registerConsoleObserver(ConsoleObserverPtr o)
{
    if (!o)
        return;

    this->AbstractServerProcess::registerConsoleObserver(o);
    PdConsoleObserver::setPdConsoleObserver(o);
    // this may be moved:
    cpd_setprinthook(&PdConsoleObserver::hookFunction);
}

void PdLocalProcess::unregisterConsoleObserver(ConsoleObserverPtr o)
{
    this->AbstractServerProcess::unregisterConsoleObserver(o);
    cpd_setprinthook(0);
}

LibraryList PdLocalProcess::loadedLibraries() const
{
    LibraryList ret;
    return ret;
}

ClassList PdLocalProcess::loadedClasses() const
{
    ClassList ret;
    std::vector<std::string> vs = cpd_system_list_loaded_classes();

    for (std::vector<std::string>::iterator it = vs.begin(); it != vs.end(); ++it) {
        ClassInfo i = ClassInfo(*it);
        ret.push_back(i);
    }
    return ret;
}

std::string PdLocalProcess::getBindObjectList()
{
    return cpd_system_list_bind_objects();
}

std::vector<std::string> PdLocalProcess::getLoadedClassesList()
{
    return cpd_system_list_loaded_classes();
}

} // namespace xpd
