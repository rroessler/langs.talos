#ifndef _TALOS_RELINT_VISITOR_HPP
#define _TALOS_RELINT_VISITOR_HPP

/// Talos Modules
#include "talos/relint/analyzer.hpp"
#include "talos/syntax/visitor.hpp"

//  MACROS  //

#define TALOS_MM_LINT_NODE(T, N, A, ...) \
    template <>                          \
    void Talos::Relint::Visitor::Acceptor::accept<Talos::Syntax::T>(const Syntax::T* N, Relint::Analyzer* A)

//  NAMESPACES  //

namespace Talos::Relint {

    /// @brief Syntax Linter Verifier.
    using Visitor = Syntax::Visitor<void, Analyzer*>;

}  // namespace Talos::Relint

namespace Talos::Syntax {

    /// @brief Visitor Specialization.
    template <>
    struct Visitor<void, Relint::Analyzer*>::Acceptor {
        //  PUBLIC METHODS  //

        template <std::derived_from<Node> T>
        static void accept(const T* node, Relint::Analyzer* analyzer);
    };

}  // namespace Talos::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) TALOS_MM_LINT_NODE(T, , );
TALOS_XX_SYNTAX_NODES(X)
#undef X

#endif
