#ifndef _XTDLIB_FILESYSTEM_READ_HPP
#define _XTDLIB_FILESYSTEM_READ_HPP

/// C++ Includes
#include <vector>

/// Library Modules
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Filesystem {

    /**
     * @brief Reads a file into memory.
     * @param file_path             File to read.
     */
    String::Buffer Read(const String::View& file_path);
    String::Buffer Read(const String::Buffer& file_path);
    String::Buffer Read(const Filesystem::Path& file_path);

    /**
     * @brief Reads a file into memory.
     * @param file_path             File to read.
     */
    std::vector<uint8_t> Bytes(const String::View& file_path);
    std::vector<uint8_t> Bytes(const String::Buffer& file_path);
    std::vector<uint8_t> Bytes(const Filesystem::Path& file_path);

}  // namespace $::Filesystem

#endif
