#ifndef _FORGE_BYTECODE_VISITOR_HPP
#define _FORGE_BYTECODE_VISITOR_HPP

/// Forge Modules
#include "forge/bytecode/allocator.hpp"
#include "forge/bytecode/compiler.hpp"
#include "forge/syntax/visitor.hpp"

//  MACROS  //

#define FORGE_MM_LOWER_NODE(T, N, C, D, ...)                           \
    template <>                                                        \
    void Forge::Bytecode::Visitor::Acceptor::accept<Forge::Syntax::T>( \
        const Syntax::T* N, Bytecode::Compiler* C, Destination D)

#define FORGE_MM_LOWER_UNIMPLEMENTED(T, N, C, D, ...) \
    FORGE_MM_LOWER_NODE(T, N, C, D, __VA_ARGS__) { C->panic(9000002, "Bytecode::Compiler::lower<Syntax::" #T ">"); }

//  NAMESPACES  //

namespace Forge::Bytecode {

    /// @brief Syntax Type Visitor.
    using Visitor = Syntax::Visitor<void, Compiler*, const Bytecode::Destination&>;

}  // namespace Forge::Bytecode

namespace Forge::Syntax {

    /// @brief Visitor Specialization.
    template <>
    struct Visitor<void, Bytecode::Compiler*, const Bytecode::Destination&>::Acceptor {
        //  TYPEDEFS  //

        /// @brief Allow fast access to syllables.
        using Syllable = Bytecode::Syllable;

        /// @brief Alias the available destintations.
        using Destination = Bytecode::Destination;

        /// @brief Alias registers and constituents.
        using Register = Bytecode::Register;
        using Accumulator = Bytecode::Accumulator;

        //  PUBLIC METHODS  //

        template <std::derived_from<Node> T>
        static void accept(const T* node, Bytecode::Compiler* compiler, Destination destination = {});
    };

}  // namespace Forge::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) FORGE_MM_LOWER_NODE(T, , , );
FORGE_XX_SYNTAX_NODES(X)
#undef X

#endif
