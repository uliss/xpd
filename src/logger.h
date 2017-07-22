#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace xpd {

class Logger {
public:
    Logger();
    virtual ~Logger();

    virtual std::ostream& log() = 0;

    template <class T>
    Logger& operator<<(const T& t)
    {
        log() << t;
        return *this;
    }
};

class StreamLogger : public Logger {
    std::ostream& stream_;

public:
    StreamLogger(std::ostream& stream);
    std::ostream& log();
};

} // namespace xpd

#endif // LOGGER_H
