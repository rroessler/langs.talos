#ifndef _XTDLIB_BLOB_BUFFER_HPP
#define _XTDLIB_BLOB_BUFFER_HPP

/// C++ Modules
#include <vector>

/// Library Modules
#include "xtdlib/string/view.hpp"

namespace $::Blob {

    /// @brief Blob View Details.
    using View = String::View;

    /// @brief Blob Buffer Details.
    using Buffer = std::vector<uint8_t>;

}  // namespace $::Blob

#endif
