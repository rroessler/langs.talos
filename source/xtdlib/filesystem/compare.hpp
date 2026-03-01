#ifndef _XTDLIB_FILESYSTEM_COMPARE_HPP
#define _XTDLIB_FILESYSTEM_COMPARE_HPP

/// C++ Includes
#include <filesystem>

/// Library Includes
#include "xtdlib/macros/forward.hpp"

/// Forward Declarations
$_FWD(using Path = std::filesystem::path, $::Filesystem)

namespace $::Filesystem {

    /// @brief Filesystem Comparison Results.
    enum class Compare : uint8_t {
        EXACT,     // a == b
        MISMATCH,  // a != b

        SUBPATH,  // a contains b
        PARENT,   // b contains a
    };

}  // namespace $::Filesystem

namespace $::Filesystem::Type {

    static constexpr auto FILE = std::filesystem::file_type::regular;
    static constexpr auto FOLDER = std::filesystem::file_type::directory;
    static constexpr auto SYMLINK = std::filesystem::file_type::symlink;

}  // namespace $::Filesystem::Type

#endif
