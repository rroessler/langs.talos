#ifndef _TALOS_SYNTAX_VISITOR_HPP
#define _TALOS_SYNTAX_VISITOR_HPP

/// Talos Includes
#include "talos/syntax/tree.hpp"

/// Inline Includes
#include "talos/syntax/_inline/annotation.ipp"
#include "talos/syntax/_inline/declaration.ipp"
#include "talos/syntax/_inline/expression.ipp"
#include "talos/syntax/_inline/statement.ipp"

//  X-MACROS  //

/// @brief All available syntax nodes.
#define TALOS_XX_SYNTAX_NODES(X) \
  TALOS_XX_EXPRESSION_NODES(X)   \
  TALOS_XX_STATEMENT_NODES(X)    \
  TALOS_XX_DECLARATION_NODES(X)  \
  TALOS_XX_ANNOTATION_NODES(X)   \
  TALOS_XX_ANONYMOUS_NODES(X)

//  NAMESPACES  //

namespace Talos::Syntax {

/// @brief Baseline Syntax Visitor.
template <class R, class... As> struct Visitor {
  //  TYPEDEFS  //

  /// @brief Acceptor instance.
  struct Acceptor;

  //  CONSTRUCTORS  //

  /// @brief Constructs a visitor instance.
  constexpr Visitor() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Handles visiting nodes.
   * @param node                      Node to visit.
   * @param args                      Arguments to forward.
   */
  $_INLINE_PERF static constexpr R visit(const Node *node, As &&...args) {
#define X(N, ...)                                                                             \
  case $::RTTI::Hash<N>(): return Acceptor::accept(node->as<N>(), std::forward<As>(args)...);
    switch (node->trivia()->hash()) {
      TALOS_XX_SYNTAX_NODES(X) // should be a suitable node to handle
    default: $_ABORT("Unknown AST Node '{0}'", node->trivia()->name());
    }
#undef X
  }
};

} // namespace Talos::Syntax

#endif
