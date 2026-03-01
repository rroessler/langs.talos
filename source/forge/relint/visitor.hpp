#ifndef _FORGE_RELINT_VISITOR_HPP
#define _FORGE_RELINT_VISITOR_HPP

/// Forge Modules
#include "forge/relint/analyzer.hpp"
#include "forge/syntax/visitor.hpp"

//  MACROS  //

#define FORGE_MM_LINT_NODE(T, N, A, ...) \
    template <>                          \
    void Forge::Relint::Visitor::Acceptor::accept<Forge::Syntax::T>(const Syntax::T* N, Relint::Analyzer* A)

//  NAMESPACES  //

namespace Forge::Relint {

    /// @brief Syntax Linter Verifier.
    using Visitor = Syntax::Visitor<void, Analyzer*>;

}  // namespace Forge::Relint

namespace Forge::Syntax {

    /// @brief Visitor Specialization.
    template <>
    struct Visitor<void, Relint::Analyzer*>::Acceptor {
        //  PUBLIC METHODS  //

        template <std::derived_from<Node> T>
        static void accept(const T* node, Relint::Analyzer* analyzer);
    };

}  // namespace Forge::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) FORGE_MM_LINT_NODE(T, , );
FORGE_XX_SYNTAX_NODES(X)
#undef X

#endif
