#ifndef _TALOS_EXPRESSION_CAST_HPP
#define _TALOS_EXPRESSION_CAST_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Cast Expression Node.
class Cast : public Mixin<Cast, Expression> {
  //  PROPERTIES  //

  /// @brief Expression value.
  Expression *m_value;

  /// @brief Expression guard.
  Annotation *m_guard;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a cast expression.
   * @param value                     Cast value.
   * @param guard                     Guard value.
   */
  explicit Cast(Expression *value, Annotation *guard) : m_value(value), m_guard(guard) {}

  //  PUBLIC METHODS  //

  inline constexpr const Expression *value() const noexcept { return m_value; }
  inline constexpr const Annotation *guard() const noexcept { return m_guard; }
};

} // namespace Talos::Syntax

#endif
