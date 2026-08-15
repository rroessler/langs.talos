#ifndef _TALOS_LITERAL_BOOLEAN_HPP
#define _TALOS_LITERAL_BOOLEAN_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief True Literal Node.
struct True : public Mixin<True, Expression> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a literal "True" value.
  explicit True() = default;
};

/// @brief False Literal Node.
struct False : public Mixin<False, Expression> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a literal "False" value.
  explicit False() = default;
};

} // namespace Talos::Syntax

#endif
