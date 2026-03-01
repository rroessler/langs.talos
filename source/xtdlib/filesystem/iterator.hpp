#ifndef _XTDLIB_FILESYSTEM_ITERATOR_HPP
#define _XTDLIB_FILESYSTEM_ITERATOR_HPP

/// Library Modules
#include "xtdlib/filesystem/path.hpp"

namespace $::Filesystem {

    /// @brief Filesystem Entry Typing.
    using Entry = std::filesystem::directory_entry;

    /// @brief Non-recursive directory iterator.
    using Iterator = std::filesystem::directory_iterator;

    /// @brief Recursive Directory Iterator.
    using Recurse = std::filesystem::recursive_directory_iterator;

}  // namespace $::Filesystem

namespace $::Filesystem::Follow {

    static constexpr auto DEFAULT = std::filesystem::directory_options::none;
    static constexpr auto SYMLINKS = std::filesystem::directory_options::follow_directory_symlink;

}  // namespace $::Filesystem::Follow

#endif
