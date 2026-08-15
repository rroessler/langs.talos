#ifndef _XTDLIB_FILESYSTEM_CHMOD_HPP
#define _XTDLIB_FILESYSTEM_CHMOD_HPP

/// Library Includes
#include "xtdlib/filesystem/path.hpp"

namespace $::FS {

/// @brief Available file-permissions.
using Permissions = std::filesystem::perms;

/// @brief Allows changing permissions.
static inline struct {
  //  PUBLIC METHODS  //

  /**
   * @brief Makes a file executable.
   * @param file_path                 File to update.
   */
  inline constexpr void executable(const Path &file_path) {
    static constexpr auto perms = Permissions::group_exec | Permissions::owner_exec | Permissions::others_exec;
    return std::filesystem::permissions(file_path, perms, std::filesystem::perm_options::add); // and emplace
  }
} Chmod;

} // namespace $::FS

#endif
