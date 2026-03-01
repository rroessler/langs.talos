#ifndef _FORGE_TYPE_VISITOR_HPP
#define _FORGE_TYPE_VISITOR_HPP

/// Forge Modules
#include "forge/syntax/visitor.hpp"
#include "forge/type/analyzer.hpp"
#include "forge/type/builder.hpp"
#include "forge/type/deduction.hpp"

//  MACROS  //

#define FORGE_MM_CHECK_NODE(T, N, A, ...)                                            \
    template <>                                                                      \
    Forge::Type::Deduction Forge::Type::Visitor::Acceptor::accept<Forge::Syntax::T>( \
        const Syntax::T* N, Type::Analyzer* A)

//  NAMESPACES  //

namespace Forge::Type {

    /// @brief Syntax Type Visitor.
    using Visitor = Syntax::Visitor<Deduction, Analyzer*>;

}  // namespace Forge::Type

namespace Forge::Syntax {

    /// @brief Visitor Specialization.
    template <>
    struct Visitor<Type::Deduction, Type::Analyzer*>::Acceptor {
        //  PUBLIC METHODS  //

        template <std::derived_from<Node> T>
        static Type::Deduction accept(const T* node, Type::Analyzer* analyzer);
    };

}  // namespace Forge::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) FORGE_MM_CHECK_NODE(T, , );
FORGE_XX_SYNTAX_NODES(X)
#undef X

#endif
