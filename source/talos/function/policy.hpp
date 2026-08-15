#ifndef _TALOS_FUNCTION_POLICY_HPP
#define _TALOS_FUNCTION_POLICY_HPP

/// Talos Includes
#include "talos/forward/function.hpp"

//  X-MACROS  //

/// @brief All available function policies.
#define TALOS_XX_FUNCTION_POLICIES(X)                \
  X(CALL, "call")   /** Normal call invocation. */   \
  X(ASYNC, "async") /** Default async invocation. */ \
  X(DEFER, "defer") /** Defers scoped execution. */  \
  X(SPAWN, "spawn") /** Custom async invocation. */

//  NAMESPACES  //

namespace Talos::Function {

/// @brief Available Function Policies.
$_XX_ENUM_CLASS(Policy, uint8_t, TALOS_XX_FUNCTION_POLICIES);

} // namespace Talos::Function

#endif
