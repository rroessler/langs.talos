#ifndef _TALOS_OPERATOR_ATTRIBUTE_HPP
#define _TALOS_OPERATOR_ATTRIBUTE_HPP

/// Talos Includes
#include "talos/operator/inspect.hpp"

namespace Talos::Operator::Attribute {

#define X(K, N, ...) static constexpr auto K = Inspect::symbol(Kind::K);
TALOS_XX_OPERATORS_CUSTOM(X)
X(CALL, "invoke")
#undef X

} // namespace Talos::Operator::Attribute

#endif
