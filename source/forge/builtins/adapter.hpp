#ifndef _FORGE_BUILTINS_ADAPTER_HPP
#define _FORGE_BUILTINS_ADAPTER_HPP

/// Forge Modules
#include "forge/forward/builtins.hpp"

namespace Forge::Builtins {

    /// @brief Associated Adapter Enumeration.
    enum class Adapter : uint8_t { FIELDS, GLOBALS, TYPEDEFS, OPERATORS };

}  // namespace Forge::Builtins

#endif
