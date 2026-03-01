/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_POSIX

/// POSIX Modules
#include <unistd.h>

/// Library Modules
#include "xtdlib/system/information.hpp"

//  PUBLIC METHODS  //

intptr_t $::System::pid() { return static_cast<intptr_t>(getpid()); }

#endif
