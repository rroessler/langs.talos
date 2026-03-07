#ifndef _TALOS_FUNCTION_POLICY_HPP
#define _TALOS_FUNCTION_POLICY_HPP

/// Talos Modules
#include "talos/forward/function.hpp"

//  X-MACROS  //

/// @brief All available function policies.
#define TALOS_XX_FUNCTION_POLICIES(X) \
    /** X(CALL, "call") */            \
    X(ASYNC, "async")                 \
    /** X(DEFER, "defer") */          \
    /** X(SPAWN, "spawn") */

//  NAMESPACES  //

namespace Talos::Function {

    /// @brief Available Function Policies.
    $_XX_ENUM_CLASS(Policy, uint8_t, TALOS_XX_FUNCTION_POLICIES);

}  // namespace Talos::Function

#endif
