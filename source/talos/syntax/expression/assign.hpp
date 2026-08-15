#ifndef _TALOS_ASSIGN_EXPRESSION_HPP
#define _TALOS_ASSIGN_EXPRESSION_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Assignment Node.
class Assign : public Mixin<Assign, Expression> {
  //  PROPERTIES  //

  /// @brief Assignment value.
  Expression *m_value;

  /// @brief Identifier name.
  Expression *m_target;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an assignment node.
   * @param target                    Assignment target.
   * @param value                     Value to assign.
   */
  explicit Assign(Expression *target, Expression *value) : m_value(value), m_target(target) {}

  //  PUBLIC METHODS  //

  inline constexpr const Expression *value() const noexcept { return m_value; }
  inline constexpr const Expression *target() const noexcept { return m_target; }
};

} // namespace Talos::Syntax

#endif
