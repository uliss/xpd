#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "observer.h"
#include <string>

namespace xpd {

class ConsoleObserver : public Observer {
    std::string text_;

public:
    ConsoleObserver();

    void setText(const std::string& text);
    const std::string& text() const;
};

} // namespace xpd

#endif // CONSOLEOBSERVER_H
