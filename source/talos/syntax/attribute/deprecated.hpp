#ifndef _TALOS_ATTRIBUTE_DEPRECATED_HPP
#define _TALOS_ATTRIBUTE_DEPRECATED_HPP

/// Talos Includes
#include "talos/diagnostic/inspect.hpp"

/// Syntax Includes
#include "talos/syntax/declaration/attribute.hpp"

namespace Talos::Syntax {

/// @brief Compile Time Deprecation Node.
class Deprecated : public Mixin<Deprecated, Attribute> {
  //  PROPERTIES  //

  /// @brief The underlying deprecation message.
  $::String::View m_message;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a deprecated attribute.
   * @param message                       Deprecation message.
   */
  explicit Deprecated(const Lexer::Token *token) : Deprecated(token->lexeme()) {}
  explicit Deprecated(const $::String::View &message = Diagnostic::Inspect::message(9000101))
      : Mixin(Reflect::Category::DEPRECATED), m_message(message) {}

  //  PUBLIC METHODS  //

  /// @brief The underlying attribute message.
  inline constexpr $::String::View message() const noexcept { return m_message; }
};

} // namespace Talos::Syntax

#endif
