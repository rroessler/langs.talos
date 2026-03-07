#ifndef _TALOS_SYNTAX_VISITOR_HPP
#define _TALOS_SYNTAX_VISITOR_HPP

/// Talos Modules
#include "talos/syntax/tree.hpp"

/// Inline Modules
#include "talos/syntax/_inline/annotation.ipp"
#include "talos/syntax/_inline/declaration.ipp"
#include "talos/syntax/_inline/expression.ipp"
#include "talos/syntax/_inline/statement.ipp"

//  X-MACROS  //

#define TALOS_XX_SYNTAX_NODES(X)  \
    TALOS_XX_LITERAL_NODES(X)     \
    TALOS_XX_PREFIX_NODES(X)      \
    TALOS_XX_INFIX_NODES(X)       \
    TALOS_XX_STATEMENT_NODES(X)   \
    TALOS_XX_ANONYMOUS_NODES(X)   \
    TALOS_XX_DECLARATION_NODES(X) \
    TALOS_XX_ANNOTATION_NODES(X)

//  NAMESPACES  //

namespace Talos::Syntax {

    /// @brief Baseline Syntax Visitor.
    template <class R, class... As>
    struct Visitor {
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
        $_INLINE_PERF static constexpr R visit(const Node* node, As&&... args) {
#define X(N, ...) \
    case $::RTTI::Hash<N>(): return Acceptor::accept(node->as<N>(), std::forward<As>(args)...);
            switch (node->traits()->tag()) {
                TALOS_XX_SYNTAX_NODES(X)  // should be a suitable node to handle
                default: $_ABORT("Unknown AST Node '{0}'", node->traits()->tag());
            }
#undef X
        }
    };

}  // namespace Talos::Syntax

#endif
