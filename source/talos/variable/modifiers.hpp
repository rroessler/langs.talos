#ifndef _TALOS_VARIABLE_MODIFIERS_HPP
#define _TALOS_VARIABLE_MODIFIERS_HPP

/// Talos Modules
#include "talos/forward/syntax.hpp"

namespace Talos::Variable {

    /// @brief Variable Flags Available.
    enum class Flag : uint16_t {
        MUTABLE,     // Denotes readonly/mutability.
        OPTIONAL,    // Whether or not a typing is optional.
        DISPOSABLE,  // Denotes if variable is disposable.

        VIRTUAL,   // Encapsulates virtual/abstract variables.
        OVERRIDE,  // Encapsulates field/virtual overrides.

        STATIC,     // Enforces static inheritance.
        PUBLIC,     // Publically available fields.
        PRIVATE,    // Privately available fields.
        PROTECTED,  // Protected object fields.

        EXPORT,  // Denotes if a variable has been exported.
        OWNED,   // Denotes if a variable is used/owned at all.
    };

    /// @brief Explicit Modifier Flags.
    using Modifiers = $::Enum::Flags<Flag>;

}  // namespace Talos::Variable

#endif
