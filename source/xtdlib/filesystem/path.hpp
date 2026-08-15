#ifndef _XTDLIB_FILESYSTEM_PATH_HPP
#define _XTDLIB_FILESYSTEM_PATH_HPP

/// Vendor Includes
#include <xhash/xhash.hpp>

/// Library Includes
#include "xtdlib/filesystem/compare.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Path {

/// @brief Gets the current-working directory.
static inline FS::Path current() { return std::filesystem::current_path(); }

/**
 * @brief Constructs a unique file-path.
 * @param prefix                    Prefix value.
 * @param suffix                    Suffix value.
 */
static inline FS::Path unique(const String::Buffer &prefix = "", const String::Buffer &suffix = "") {
  return std::filesystem::temp_directory_path() / (prefix + XH::UUID::V4().to_string() + suffix);
}

/**
 * @brief Gets a file-paths extension.
 * @param file_path                 File to query.
 */
static inline FS::Path extension(const FS::Path &file_path) { return file_path.extension(); }

/**
 * @brief Gets a file-paths file name.
 * @param file_path                 File to query.
 */
static inline FS::Path filename(const FS::Path &file_path) { return file_path.filename(); }

/**
 * @brief Gets a file-paths directory name.
 * @param file_path                 File to query.
 */
static inline FS::Path dirname(const FS::Path &file_path) { return file_path.parent_path(); }

/**
 * @brief Gets a relative path value.
 * @param absolute                  File to resolve.
 */
FS::Path relative(const FS::Path &absolute, const FS::Path &hint = current());

/**
 * @brief Gets an relative path value.
 * @param relative                  File to resolve.
 */
FS::Path absolute(const FS::Path &relative, const FS::Path &hint = current());

/**
 * @brief Gets a canonical path value.
 * @param relative                  File to resolve.
 */
FS::Path canonical(const FS::Path &relative, const FS::Path &hint = current());

/**
 * @brief Denotes if a file-path contains a base.
 * @param file_path                 Path to validate.
 * @param base                      Base path to check.
 */
FS::Compare compare(const FS::Path &file_path, const FS::Path &base);

/**
 * @brief Checks if a file-path exists.
 * @param file_path                 File to check.
 */
static inline bool exists(const FS::Path &file_path) { return std::filesystem::exists(file_path); }

/**
 * @brief Checks if a file-path is a file.
 * @param file_path                 File to check.
 */
static inline bool is_file(const FS::Path &file_path) { return std::filesystem::is_regular_file(file_path); }

/**
 * @brief Checks if a file-path is a directory.
 * @param file_path                 File to check.
 */
static inline bool is_directory(const FS::Path &file_path) { return std::filesystem::is_directory(file_path); }

/**
 * @brief Checks if a file-path is a symlink.
 * @param file_path                 File to check.
 */
static inline bool is_symlink(const FS::Path &file_path) { return std::filesystem::is_symlink(file_path); }

/**
 * @brief Handles joining paths together.
 * @param args                      Segments to join.
 */
template <std::convertible_to<FS::Path>... As> static inline FS::Path join(As &&...args) {
  return (FS::Path(args) / ...);
}

} // namespace $::Path

#endif
