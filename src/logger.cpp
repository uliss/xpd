#include "logger.h"

namespace xpd {

Logger::Logger()
{
}

Logger::~Logger()
{
}

std::ostream& Logger::log()
{
    return std::cout;
}

StreamLogger::StreamLogger(std::ostream& stream)
    : stream_(stream)
{
}

std::ostream& StreamLogger::log()
{
    return stream_;
}

} // namespace xpd
