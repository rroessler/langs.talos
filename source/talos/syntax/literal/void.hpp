#ifndef _TALOS_LITERAL_VOID_HPP
#define _TALOS_LITERAL_VOID_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Void Literal Node.
struct Void : public Mixin<Void, Expression> {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  explicit Void() = default;
};

} // namespace Talos::Syntax

#endif
