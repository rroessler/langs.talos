#ifndef _XTDLIB_FSYS_PATH_HPP
#define _XTDLIB_FSYS_PATH_HPP

/// Library Includes
#include "xtdlib/filesystem/compare.hpp"

namespace $::Path {

    /// @brief Gets the current-working directory.
    static inline Filesystem::Path current() { return std::filesystem::current_path(); }

    /**
     * @brief Constructs a unique file-path.
     * @param prefix                    Prefix value.
     * @param suffix                    Suffix value.
     */
    static inline Filesystem::Path unique(const String::Buffer& prefix = "", const String::Buffer& suffix = "") {
        return std::filesystem::temp_directory_path() / (prefix + XH::UUID::V4().to_string() + suffix);
    }

    /**
     * @brief Gets a file-paths extension.
     * @param file_path                 File to query.
     */
    static inline Filesystem::Path extension(const Filesystem::Path& file_path) { return file_path.extension(); }

    /**
     * @brief Gets a file-paths file name.
     * @param file_path                 File to query.
     */
    static inline Filesystem::Path filename(const Filesystem::Path& file_path) { return file_path.filename(); }

    /**
     * @brief Gets a file-paths directory name.
     * @param file_path                 File to query.
     */
    static inline Filesystem::Path dirname(const Filesystem::Path& file_path) { return file_path.parent_path(); }

    /**
     * @brief Gets a relative path value.
     * @param absolute                  File to resolve.
     */
    Filesystem::Path relative(const Filesystem::Path& absolute, const Filesystem::Path& hint = current());

    /**
     * @brief Gets an relative path value.
     * @param relative                  File to resolve.
     */
    Filesystem::Path absolute(const Filesystem::Path& relative, const Filesystem::Path& hint = current());

    /**
     * @brief Gets a canonical path value.
     * @param relative                  File to resolve.
     */
    Filesystem::Path canonical(const Filesystem::Path& relative, const Filesystem::Path& hint = current());

    /**
     * @brief Denotes if a file-path contains a base.
     * @param file_path                 Path to validate.
     * @param base                      Base path to check.
     */
    Filesystem::Compare compare(const Filesystem::Path& file_path, const Filesystem::Path& base);

    /**
     * @brief Checks if a file-path exists.
     * @param file_path                 File to check.
     */
    static inline bool exists(const Filesystem::Path& file_path) { return std::filesystem::exists(file_path); }

    /**
     * @brief Checks if a file-path is a file.
     * @param file_path                 File to check.
     */
    static inline bool is_file(const Filesystem::Path& file_path) {
        return std::filesystem::is_regular_file(file_path);
    }

    /**
     * @brief Checks if a file-path is a directory.
     * @param file_path                 File to check.
     */
    static inline bool is_directory(const Filesystem::Path& file_path) {
        return std::filesystem::is_directory(file_path);
    }

    /**
     * @brief Checks if a file-path is a symlink.
     * @param file_path                 File to check.
     */
    static inline bool is_symlink(const Filesystem::Path& file_path) { return std::filesystem::is_symlink(file_path); }

    /**
     * @brief Handles joining paths together.
     * @param args                      Segments to join.
     */
    template <std::convertible_to<Filesystem::Path>... As>
    static inline Filesystem::Path join(As&&... args) {
        return (Filesystem::Path(args) / ...);
    }

}  // namespace $::Path

#endif
