#ifndef _TALOS_STATEMENT_CONTINUE_HPP
#define _TALOS_STATEMENT_CONTINUE_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Continue Statement.
struct Continue : public Mixin<Continue, Statement> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a control statement.
  explicit Continue() = default;
};

} // namespace Talos::Syntax

#endif
