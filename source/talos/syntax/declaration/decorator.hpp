#ifndef _TALOS_DECLARATION_DECORATOR_HPP
#define _TALOS_DECLARATION_DECORATOR_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Runtime Decorator Node.
class Decorator : public Mixin<Decorator> {
  //  PROPERTIES  //

  /// @brief Bound decoration value.
  Expression *m_expression;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a runtime decorator.
   * @param expression                Value to encapsulate.
   */
  explicit Decorator(Expression *expression) : m_expression(expression) {}

  //  PUBLIC METHODS  //

  /// @brief The decorator expression to be called.
  inline constexpr const Expression *expression() const noexcept { return m_expression; }
};

} // namespace Talos::Syntax

#endif
