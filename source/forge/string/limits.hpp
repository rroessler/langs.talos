#ifndef _FORGE_STRING_LIMITS_HPP
#define _FORGE_STRING_LIMITS_HPP

/// Forge Modules
#include "forge/forward/string.hpp"
#include "forge/value/common.hpp"

namespace Forge::String::Limits {

    /// @brief How big a small tagged string is.
    static constexpr size_t SMALL = Pointer::Alignment::VALUE - 1;

}  // namespace Forge::String::Limits

#endif
