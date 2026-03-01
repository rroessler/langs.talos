/// Platform Modules
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_DARWIN

/// Darwin Modules
#include <mach-o/dyld.h>

/// Platform Modules
#include "xtdlib/debug/assert.hpp"
#include "xtdlib/system/executable.hpp"

//  PUBLIC METHODS  //

$::Filesystem::Path $::Executable::resolve() {
    char file_path[PATH_MAX + 1];
    uint32_t size = sizeof(file_path);

    // attempt initially resolving the instance
    if (_NSGetExecutablePath(file_path, &size) == 0) return file_path;

    // otherwise attempt via the given size now
    String::Buffer buffer;
    buffer.resize(size);

    // should usually be valid now
    if (_NSGetExecutablePath(&buffer[0], &size) == 0) return buffer;

    // failed to retrieve a valid executable path
    $_ABORT("Failed to retreive executable path");
}

#endif
