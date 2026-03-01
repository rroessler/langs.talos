/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_LINUX

/// Platform Modules
#include "xtdlib/system/executable.hpp"

//  PUBLIC METHODS  //

$::Filesystem::Path $::Executable::resolve() { return std::filesystem::canonical("/proc/self/exe"); }

#endif
