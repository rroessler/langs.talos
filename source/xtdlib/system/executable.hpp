#ifndef _XTDLIB_SYSTEM_EXECUTABLE_HPP
#define _XTDLIB_SYSTEM_EXECUTABLE_HPP

/// Library Modules
#include "xtdlib/filesystem/path.hpp"

namespace $::Executable {

    /// @brief Resolves the full executable path.
    Filesystem::Path resolve();

    /// @brief Gets the executable file-name.
    static inline Filesystem::Path filename() { return Path::filename(resolve()); }

    /// @brief Gets the executable directory name.
    static inline Filesystem::Path dirname() { return Path::dirname(resolve()); }

}  // namespace $::Executable

#endif
