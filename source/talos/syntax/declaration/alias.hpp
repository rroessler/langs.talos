#ifndef _TALOS_DECLARATION_ALIAS_HPP
#define _TALOS_DECLARATION_ALIAS_HPP

/// Syntax Includes
#include "talos/syntax/annotation/generics.hpp"
#include "talos/syntax/declaration/preamble.hpp"

namespace Talos::Syntax {

/// @brief Type Declaration Node.
class Alias : public Mixin<Alias, Declaration> {
  //  PROPERTIES  //

  /// @brief Type annotation value.
  Annotation *m_hint;

  /// @brief Generics template to be used.
  Template m_generics = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a type declaration.
   * @param name                      Target name.
   * @param hint                      Type annotation.
   * @param generics                  Template generics.
   */
  explicit Alias(const $::String::View &name, Annotation *hint, const Template &generics = {})
      : Mixin(name), m_hint(hint), m_generics(generics) {}

  /**
   * @brief Constructs a type declaration.
   * @param target                    Target name.
   * @param hint                      Type annotation.
   * @param generics                  Template generics.
   */
  explicit Alias(const Lexer::Token *target, Annotation *hint, const Template &generics = {})
      : Mixin(target), m_hint(hint), m_generics(generics) {}

  //  PUBLIC METHODS  //

  inline constexpr const Annotation *hint() const noexcept { return m_hint; }
  inline constexpr const Template &generics() const noexcept { return m_generics; }
};

} // namespace Talos::Syntax

#endif
