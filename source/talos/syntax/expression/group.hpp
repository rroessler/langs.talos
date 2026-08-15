#ifndef _TALOS_EXPRESSION_GROUP_HPP
#define _TALOS_EXPRESSION_GROUP_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Group Expression.
class Group : public Mixin<Group, Expression> {
  //  PROPERTIES  //

  /// @brief Associated statement value.
  Expression *m_value;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a grouped expression.
   * @param value                     Grouped value.
   */
  explicit Group(Expression *value) : m_value(value) {}

  //  PUBLIC METHODS  //

  /// @brief Encpasulated panic value.
  inline constexpr const Expression *value() const noexcept { return m_value; }
};

} // namespace Talos::Syntax

#endif
