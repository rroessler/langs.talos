#ifndef _XTDLIB_FILESYSTEM_WRITE_HPP
#define _XTDLIB_FILESYSTEM_WRITE_HPP

/// C++ Modules
#include <fstream>

/// Library Modules
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Filesystem {

    /// @brief Output file-stream typing.
    using Output = std::ofstream;

    /// @brief File Writer Structure.
    static inline struct {
        //  PROPERTIES  //

        /// @brief Explicit overwrite-mode value.
        const std::ios_base::openmode mode = std::ios_base::binary | std::ios_base::trunc;

        //  OPERATOR METHODS  //

        /**
         * @brief Handles overwriting a file.
         * @param file_path             File to overwrite.
         * @param buffer                Buffer to write.
         */
        inline constexpr void operator()(const Path& file_path, const String::View& buffer) const noexcept {
            Output(file_path, mode).write(buffer.data(), buffer.size());
        }

        /**
         * @brief Handles overwriting a file.
         * @param file_path             File to overwrite.
         * @param buffer                Buffer to write.
         */
        inline constexpr void operator()(const Path& file_path, const std::vector<uint8_t>& buffer) const noexcept {
            Output(file_path, mode).write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        }
    } Overwrite;

    /// @brief File Append Structure.
    static inline struct {
        //  PROPERTIES  //

        /// @brief Explicit append-mode value.
        const std::ios_base::openmode mode = std::ios_base::binary | std::ios_base::app;

        //  OPERATOR METHODS  //

        /**
         * @brief Handles appending to a file.
         * @param file_path             File to append.
         * @param buffer                Buffer to write.
         */
        inline constexpr void operator()(const Path& file_path, const String::View& buffer) const noexcept {
            Output(file_path, mode).write(buffer.data(), buffer.size());
        }

        /**
         * @brief Handles appending to a file.
         * @param file_path             File to append.
         * @param buffer                Buffer to write.
         */
        inline constexpr void operator()(const Path& file_path, const std::vector<uint8_t>& buffer) const noexcept {
            Output(file_path, mode).write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        }
    } Append;

    /// @brief File Creation Structure.
    static inline struct {
        //  OPERATOR METHODS  //

        /**
         * @brief Constructs a new file.
         * @param file_path             File to create.
         * @param force                 Ignore failures.
         */
        inline constexpr Output operator()(const Path& file_path, bool force = false) const noexcept {
            if (!force && $::Path::exists(file_path)) throw std::system_error(EEXIST, std::generic_category());
            return std::filesystem::create_directories(file_path.parent_path()), Output(file_path, Append.mode);
        }
    } Touch;

}  // namespace $::Filesystem

#endif
