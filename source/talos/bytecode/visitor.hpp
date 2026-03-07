#ifndef _TALOS_BYTECODE_VISITOR_HPP
#define _TALOS_BYTECODE_VISITOR_HPP

/// Talos Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/compiler.hpp"
#include "talos/syntax/visitor.hpp"

//  MACROS  //

#define TALOS_MM_LOWER_NODE(T, N, C, D, ...)                           \
    template <>                                                        \
    void Talos::Bytecode::Visitor::Acceptor::accept<Talos::Syntax::T>( \
        const Syntax::T* N, Bytecode::Compiler* C, Destination D)

#define TALOS_MM_LOWER_UNIMPLEMENTED(T, N, C, D, ...) \
    TALOS_MM_LOWER_NODE(T, N, C, D, __VA_ARGS__) { C->panic(9000002, "Bytecode::Compiler::lower<Syntax::" #T ">"); }

//  NAMESPACES  //

namespace Talos::Bytecode {

    /// @brief Syntax Type Visitor.
    using Visitor = Syntax::Visitor<void, Compiler*, const Bytecode::Destination&>;

}  // namespace Talos::Bytecode

namespace Talos::Syntax {

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

}  // namespace Talos::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) TALOS_MM_LOWER_NODE(T, , , );
TALOS_XX_SYNTAX_NODES(X)
#undef X

#endif
