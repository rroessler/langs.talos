#ifndef _TALOS_SYNTAX_GRAMMAR_HPP
#define _TALOS_SYNTAX_GRAMMAR_HPP

/// Talos Includes
#include "talos/forward/parser.hpp"
#include "talos/lexer/kind.hpp"
#include "talos/syntax/precedence.hpp"

/// Forward Declarations
$_FWD(Talos::Syntax::Grammar, template <class, class> struct Rule)

namespace Talos::Syntax::Grammar {

/// @brief Expected prefix handler.
template <class R, class P> using Prefix = R *(*)(P *, bool);

/// @brief Expected infix handler.
template <class R, class P> using Infix = R *(*)(P *, R *, bool);

/// @brief Grammar Type Definition.
template <class R, class P> using Table = std::array<Rule<R, P>, static_cast<size_t>(Lexer::Kind::MISC_MAX) + 1>;

/// @brief Syntax Grammar Rule.
template <class R, class P> struct Rule {
  //  PROPERTIES  //

  /// @brief Infix callback handler.
  Infix<R, P> infix = nullptr;

  /// @brief Prefix callback handler.
  Prefix<R, P> prefix = nullptr;

  /// @brief Associated precedence value.
  Precedence rank = Precedence::NONE;

  //  CONSTRUCTORS  //

  /// @brief Default rule constructor.
  constexpr Rule() = default;

  /**
   * @brief Handles constructing a parse rule.
   * @param prefix                          Prefix function.
   * @param rank                            Operator precedence.
   */
  constexpr Rule(auto prefix) : prefix(prefix), rank(Precedence::NONE) {}

  /**
   * @brief Handles constructing a parse rule.
   * @param infix                           Infix function.
   * @param rank                            Operator precedence.
   */
  constexpr Rule(auto infix, Precedence rank) : infix(infix), rank(rank) {}

  /**
   * @brief Handles constructing a parse rule.
   * @param prefix                          Prefix function.
   * @param infix                           Infix function.
   * @param rank                            Operator precedence.
   */
  constexpr Rule(auto prefix, auto infix, Precedence rank) : infix(infix), prefix(prefix), rank(rank) {}
};

} // namespace Talos::Syntax::Grammar

#endif
