#include "pd_localprocess.h"
#include "cpd/cpd.h"
#include "pd_canvas.h"
#include "pd_consoleobserver.h"
#include "cpd/cpd_list.h"
#include "pd_objectobserver.h"

namespace xpd {

std::map<t_cpd_object*,ObserverPtr> PdLocalProcess::objectObserverMap;

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

void PdLocalProcess::receiverCallback(t_cpd_list* msg)
{
    if (cpd_list_size(msg)<1)
        return;

    t_cpd_atom * a = cpd_list_at(msg,0);
    t_cpd_symbol* s = cpd_atom_get_symbol(a);

    if (!s)
        return;

    std::string sym = cpd_symbol_name(s);

    // UI object pointer
    if (sym == "pd_ui_object")
    {
        if (cpd_list_size(msg)<3)
            return;

        a = cpd_list_at(msg,1);

        long lPtr =  static_cast<long>(cpd_atom_get_float(a));
        t_cpd_object* objPtr = reinterpret_cast<t_cpd_object*>(lPtr);

        if (!objPtr)
            return;

        if (!PdLocalProcess::objectObserverMap[objPtr])
                return;

        ObserverPtr p = PdLocalProcess::objectObserverMap[objPtr];
        PdObjectObserver *observer = reinterpret_cast<PdObjectObserver*>(p.get());

        // todo:
        t_cpd_list* o = cpd_list_new(cpd_list_size(msg)-2);
        for (int i=2; i<cpd_list_size(msg); i++)
        {
            cpd_list_append(o, cpd_list_at(msg,i));
        }

        observer->setData(o);
        observer->update();

    }

}

} // namespace xpd
