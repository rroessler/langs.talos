/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// C++ Modules
#include <iostream>

/// Library Modules
#include "xtdlib/portable/windows.hpp"
#include "xtdlib/stream/setup.hpp"

//  CONSTRUCTORS  //

$::Stream::Setup::Setup() {
    ::SetConsoleOutputCP(CP_UTF8);
    ::setvbuf(stdout, nullptr, _IOFBF, 1000);
    std::ios_base::sync_with_stdio(false);
}

#endif
