#ifndef _TALOS_STATEMENT_BREAK_HPP
#define _TALOS_STATEMENT_BREAK_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Break Statement.
struct Break : public Mixin<Break, Statement> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a control statement.
  explicit Break() = default;
};

} // namespace Talos::Syntax

#endif
