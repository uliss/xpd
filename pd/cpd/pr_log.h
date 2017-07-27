#ifndef PR_LOG_H
#define PR_LOG_H

#include "spdlog/spdlog.h"

std::shared_ptr<spdlog::logger>& console();

#endif // PR_LOG_H
