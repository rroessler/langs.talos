#ifndef _TALOS_RELINT_RULES_IPP
#define _TALOS_RELINT_RULES_IPP

/// Talos Includes
#include "talos/relint/context.hpp"
#include "talos/relint/service.hpp"

//  X-MACROS  //

#define TALOS_XX_RELINT_RULES(X)                    \
  X(NO_EMPTY_BLOCKS, "no-empty-blocks")             \
  X(NO_UNSAFE_ACCESSORS, "no-unsafe-accessors")     \
  X(NO_UNSAFE_ASSIGNMENTS, "no-unsafe-assignments") \
  X(NO_UNSAFE_CALLS, "no-unsafe-calls")             \
  X(NO_UNSAFE_RETURNS, "no-unsafe-returns")

//  NAMESPACES  //

namespace Talos::Relint::Label {

#define X(N, L, ...) static constexpr $::String::Literal N = L;
TALOS_XX_RELINT_RULES(X)
#undef X

} // namespace Talos::Relint::Label

#endif
