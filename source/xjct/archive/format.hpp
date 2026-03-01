#ifndef _XJCT_ARCHIVE_FORMAT_HPP
#define _XJCT_ARCHIVE_FORMAT_HPP

/// XJCT Modules
#include "xjct/forward/archive.hpp"

namespace XJCT::Archive {

    /// @brief Imbument format typing.
    enum class Format : uint8_t { DARWIN, LINUX, WINDOWS, UNKNOWN };

    /// @brief Available platform extensions.
    static inline constexpr $::String::View Extension = $_PLATFORM_WINDOWS ? ".exe" : "";

}  // namespace XJCT::Archive

#endif
