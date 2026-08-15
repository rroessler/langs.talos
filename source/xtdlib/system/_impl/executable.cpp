/// Library Includes
#include "xtdlib/system/executable.hpp"

/// @brief Gets the executable file-name.
$::FS::Path $::Executable::filename() { return Path::filename(resolve()); }

/// @brief Gets the executable directory name.
$::FS::Path $::Executable::dirname() { return Path::dirname(resolve()); }
