#ifndef _TALOS_ATTRIBUTE_OVERRIDE_HPP
#define _TALOS_ATTRIBUTE_OVERRIDE_HPP

/// Talos Includes
#include "talos/operator/inspect.hpp"

/// Syntax Includes
#include "talos/syntax/declaration/attribute.hpp"

namespace Talos::Syntax {

/// @brief Compile Time Operator Node.
class Override : public Mixin<Override, Attribute> {
  //  PROPERTIES  //

  /// @brief The underlying operator kind.
  Operator::Kind m_kind;

  /// @brief Allow setting the target.
  Expression *m_target;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an operator overload.
   * @param kind              Kind of operator.
   * @param target            Target to overload.
   */
  explicit Override(Operator::Kind kind, Expression *target = nullptr) :
      Mixin(Reflect::Category::OPERATOR), m_kind(kind), m_target(target) {}

  //  PUBLIC METHODS  //

  inline constexpr Operator::Kind kind() const noexcept { return m_kind; }
  inline constexpr const Expression *target() const noexcept { return m_target; }
  inline constexpr $::String::View label() const noexcept { return ::Talos::Operator::Inspect::name(m_kind); }
  inline constexpr $::String::View symbol() const noexcept { return ::Talos::Operator::Inspect::symbol(m_kind); }
};

} // namespace Talos::Syntax

#endif
