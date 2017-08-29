#ifndef PD_CONSOLEOBSERVER_H
#define PD_CONSOLEOBSERVER_H

#include "consoleobserver.h"
#include <string>

namespace xpd {

// move this declaration
typedef std::shared_ptr<ConsoleObserver> ConsoleObserverPtr;

class PdConsoleObserver : public ConsoleObserver {
    static ConsoleObserverPtr _pdConsoleObserver;
public:
    static void hookFunction(const char* str);

    // stub
    static void setPdConsoleObserver(ConsoleObserverPtr o);
};

} // namespace xpd

#endif // PD_CONSOLEOBSERVER_H
