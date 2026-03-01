/// Library Modules
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_POSIX

/// Unix Modules
#include <unistd.h>

//  PUBLIC METHODS  //

bool $::Terminal::is(int32_t fh) { return ::isatty(fh); }

#endif
