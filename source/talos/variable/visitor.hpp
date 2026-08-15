#ifndef _TALOS_VARIABLE_VISITOR_HPP
#define _TALOS_VARIABLE_VISITOR_HPP

/// Talos Includes
#include "talos/syntax/visitor.hpp"
#include "talos/variable/analyzer.hpp"

/// Forward Declarations
$_FWD(Talos::Variable, using Visitor = Syntax::Visitor<void, Analyzer *>)

//  MACROS  //

/// @brief Allows variable capturing of nodes.
#define TALOS_MM_CAPTURE_NODE(T, N, A, ...)                                                                      \
  template <> void Talos::Variable::Visitor::Acceptor::accept<Talos::Syntax::T>(const Syntax::T *N, Analyzer *A)

//  NAMESPACES  //

namespace Talos::Syntax {

/// @brief Visitor Specialization.
template <> struct Visitor<void, ::Talos::Variable::Analyzer *>::Acceptor {
  //  TYPEDEFS  //

  /// @brief Aliased analyzer instance.
  using Analyzer = ::Talos::Variable::Analyzer;

  //  PUBLIC METHODS  //

  /// @brief Allows visiting syntax nodes for analysis.
  template <std::derived_from<Node> T> static void accept(const T *node, Analyzer *analyzer);
};

} // namespace Talos::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) TALOS_MM_CAPTURE_NODE(T, , );
TALOS_XX_SYNTAX_NODES(X)
#undef X

#endif
