#ifndef _FORGE_SYNTAX_VISITOR_HPP
#define _FORGE_SYNTAX_VISITOR_HPP

/// Forge Modules
#include "forge/syntax/tree.hpp"

/// Inline Modules
#include "forge/syntax/_inline/annotation.ipp"
#include "forge/syntax/_inline/declaration.ipp"
#include "forge/syntax/_inline/expression.ipp"
#include "forge/syntax/_inline/statement.ipp"

//  X-MACROS  //

#define FORGE_XX_SYNTAX_NODES(X)  \
    FORGE_XX_LITERAL_NODES(X)     \
    FORGE_XX_PREFIX_NODES(X)      \
    FORGE_XX_INFIX_NODES(X)       \
    FORGE_XX_STATEMENT_NODES(X)   \
    FORGE_XX_ANONYMOUS_NODES(X)   \
    FORGE_XX_DECLARATION_NODES(X) \
    FORGE_XX_ANNOTATION_NODES(X)

//  NAMESPACES  //

namespace Forge::Syntax {

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
                FORGE_XX_SYNTAX_NODES(X)  // should be a suitable node to handle
                default: $_ABORT("Unknown AST Node '{0}'", node->traits()->tag());
            }
#undef X
        }
    };

}  // namespace Forge::Syntax

#endif
