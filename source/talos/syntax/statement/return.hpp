#ifndef _TALOS_STATEMENT_RETURN_HPP
#define _TALOS_STATEMENT_RETURN_HPP

/// Talos Includes
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

/// @brief Return Statement.
class Return : public Mixin<Return, Statement> {
  //  PROPERTIES  //

  /// @brief Associated statement value.
  Expression *m_value = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a "return" statement.
   * @param value                     Value to return.
   */
  explicit Return(Expression *value = nullptr) : m_value(value) {}

  //  PUBLIC METHODS  //

  /// @brief Encpasulated return value.
  inline constexpr const Expression *value() const noexcept { return m_value; }
};

} // namespace Talos::Syntax

#endif
