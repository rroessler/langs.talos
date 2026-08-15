#ifndef _TALOS_EXPRESSION_CALL_HPP
#define _TALOS_EXPRESSION_CALL_HPP

/// Talos Includes
#include "talos/function/policy.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Call Expression Node.
class Call : public Mixin<Call, Expression> {
  //  PROPERTIES  //

  /// @brief Callee expression value.
  Expression *m_callee;

  /// @brief Calling arguments.
  std::vector<Expression *> m_arguments;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a call expression.
   * @param callee                    Callee value.
   * @param arguments                 Bound arguments.
   */
  explicit Call(Expression *callee, const std::vector<Expression *> &arguments = {})
      : m_callee(callee), m_arguments(arguments) {}

  //  PUBLIC METHODS  //

  inline constexpr const Expression *callee() const noexcept { return m_callee; }
  inline constexpr const std::vector<Expression *> &arguments() const noexcept { return m_arguments; }
};

} // namespace Talos::Syntax

#endif
