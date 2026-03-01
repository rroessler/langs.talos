#ifndef _FORGE_FUNCTION_POLICY_HPP
#define _FORGE_FUNCTION_POLICY_HPP

/// Forge Modules
#include "forge/forward/function.hpp"

//  X-MACROS  //

/// @brief All available function policies.
#define FORGE_XX_FUNCTION_POLICIES(X) \
    /** X(CALL, "call") */            \
    X(ASYNC, "async")                 \
    /** X(DEFER, "defer") */          \
    /** X(SPAWN, "spawn") */

//  NAMESPACES  //

namespace Forge::Function {

    /// @brief Available Function Policies.
    $_XX_ENUM_CLASS(Policy, uint8_t, FORGE_XX_FUNCTION_POLICIES);

}  // namespace Forge::Function

#endif
