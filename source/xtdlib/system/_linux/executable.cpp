/// Platform Includes
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_LINUX

/// Platform Includes
#include "xtdlib/system/executable.hpp"

//  PUBLIC METHODS  //

$::FS::Path $::Executable::resolve() { return std::filesystem::canonical("/proc/self/exe"); }

#endif
