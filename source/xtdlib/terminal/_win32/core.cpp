/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Platform Modules
#include "xtdlib/portable/windows.hpp"
#include "xtdlib/terminal/core.hpp"

//  PUBLIC METHODS  //

void $::Terminal::utf8() {
  ::SetConsoleOutputCP(CP_UTF8);
  ::setvbuf(stdout, nullptr, _IOFBF, 1000);
}

#endif
