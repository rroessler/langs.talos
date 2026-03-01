/// Library Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Library Modules
#include "xtdlib/portable/windows.hpp"
#include "xtdlib/system/information.hpp"

//  PUBLIC METHODS  //

intptr_t $::System::pid() { return static_cast<intptr_t>(::GetCurrentProcessId()); }

#endif
