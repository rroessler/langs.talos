/// Library Modules
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Windows Modules
#include "xtdlib/portable/windows.hpp"

//  PUBLIC METHODS  //

bool $::Terminal::is(int32_t fh) { return ::_isatty(fh); }

#endif
