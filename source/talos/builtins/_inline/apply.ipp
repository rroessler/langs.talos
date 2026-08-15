#ifndef _TALOS_BUILTINS_APPLY_IPP
#define _TALOS_BUILTINS_APPLY_IPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

namespace Talos::Builtins {

/// @brief Operator Decision Tree.
template <class T> struct Apply : private $::Ensure::Static {
  //  PUBLIC METHODS  //

  static Type::Erased unary(const Type::Structure *self, Operator::Kind kind);
  static Type::Erased binary(const Type::Structure *self, Operator::Kind kind, const Type::Erased &right);

  /**
   * @brief Handles delegating type operators.
   * @param self                    Structure typing.
   * @param kind                    Operator kind.
   * @param right                   Optional RHS type.
   */
  static inline constexpr Type::Erased
  decide(const Type::Structure *self, Operator::Kind kind, const Type::Erased &right) {
    return right == nullptr ? unary(self, kind) : binary(self, kind, right);
  }
};

} // namespace Talos::Builtins

#endif
