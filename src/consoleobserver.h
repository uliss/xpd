#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "observer.h"
#include <string>

using namespace std;

namespace xpd {

class ConsoleObserver : public Observer {
    string _text;
public:
    ConsoleObserver();
    
    void setText(string text);
    string text();
};

} // namespace xpd

#endif // CONSOLEOBSERVER_H
