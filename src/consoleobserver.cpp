#include "consoleobserver.h"

namespace xpd {

ConsoleObserver::ConsoleObserver()
{
}

void ConsoleObserver::setText(string text)
{
    _text = text;
};

string ConsoleObserver::text()
{
    return _text;
};

} // namespace xpd
