#ifndef _XTDLIB_SYSTEM_EXECUTABLE_HPP
#define _XTDLIB_SYSTEM_EXECUTABLE_HPP

/// Library Includes
#include "xtdlib/filesystem/path.hpp"

namespace $::Executable {

/// @brief Resolves the full executable path.
FS::Path resolve();

/// @brief Gets the executable file-name.
FS::Path filename();

/// @brief Gets the executable directory name.
FS::Path dirname();

} // namespace $::Executable

#endif
