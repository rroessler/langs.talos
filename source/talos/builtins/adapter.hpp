#ifndef _TALOS_BUILTINS_ADAPTER_HPP
#define _TALOS_BUILTINS_ADAPTER_HPP

/// Talos Modules
#include "talos/forward/builtins.hpp"

namespace Talos::Builtins {

    /// @brief Associated Adapter Enumeration.
    enum class Adapter : uint8_t { FIELDS, GLOBALS, TYPEDEFS, OPERATORS };

}  // namespace Talos::Builtins

#endif
