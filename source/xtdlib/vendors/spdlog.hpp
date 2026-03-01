#ifndef _XTDLOG_VENDORS_SPDLOG_HPP
#define _XTDLOG_VENDORS_SPDLOG_HPP

#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "I", "W", "E", "F", "O" }
#define SPDLOG_LEVEL_NAMES { "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL", "OFF" }

/// Library Modules
#include "xtdlib/vendors/_fwd.hpp"

/// Vendor Modules
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#endif
