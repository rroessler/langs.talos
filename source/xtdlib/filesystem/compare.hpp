#ifndef _XTDLIB_FILESYSTEM_COMPARE_HPP
#define _XTDLIB_FILESYSTEM_COMPARE_HPP

/// Library Includes
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/portable/stdlib.hpp"

/// Forward Declarations
$_FWD($::FS, using Path = std::filesystem::path)

namespace $::FS {

/// @brief Filesystem Comparison Results.
enum class Compare : uint8_t {
  EXACT,    // a == b
  MISMATCH, // a != b

  SUBPATH, // a contains b
  PARENT,  // b contains a
};

} // namespace $::FS

#endif
