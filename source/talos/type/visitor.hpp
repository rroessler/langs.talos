#ifndef _TALOS_TYPE_VISITOR_HPP
#define _TALOS_TYPE_VISITOR_HPP

/// Talos Modules
#include "talos/syntax/visitor.hpp"
#include "talos/type/analyzer.hpp"
#include "talos/type/builder.hpp"
#include "talos/type/deduction.hpp"

//  MACROS  //

#define TALOS_MM_CHECK_NODE(T, N, A, ...)                                            \
    template <>                                                                      \
    Talos::Type::Deduction Talos::Type::Visitor::Acceptor::accept<Talos::Syntax::T>( \
        const Syntax::T* N, Type::Analyzer* A)

//  NAMESPACES  //

namespace Talos::Type {

    /// @brief Syntax Type Visitor.
    using Visitor = Syntax::Visitor<Deduction, Analyzer*>;

}  // namespace Talos::Type

namespace Talos::Syntax {

    /// @brief Visitor Specialization.
    template <>
    struct Visitor<Type::Deduction, Type::Analyzer*>::Acceptor {
        //  PUBLIC METHODS  //

        template <std::derived_from<Node> T>
        static Type::Deduction accept(const T* node, Type::Analyzer* analyzer);
    };

}  // namespace Talos::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) TALOS_MM_CHECK_NODE(T, , );
TALOS_XX_SYNTAX_NODES(X)
#undef X

#endif
