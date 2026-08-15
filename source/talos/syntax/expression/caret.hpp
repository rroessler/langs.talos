#ifndef _TALOS_EXPRESSION_CARET_HPP
#define _TALOS_EXPRESSION_CARET_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Caret Expression Node.
struct Caret : public Mixin<Caret, Expression> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a caret expression.
  explicit Caret() = default;
};

} // namespace Talos::Syntax

#endif
