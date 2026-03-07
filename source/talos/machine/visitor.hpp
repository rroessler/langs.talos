#ifndef _TALOS_MACHINE_VISITOR_HPP
#define _TALOS_MACHINE_VISITOR_HPP

/// Talos Modules
#include "talos/machine/builder.hpp"

//  MACROS  //

#define TALOS_MM_MACHINE_EMIT(N, B, I, ...)                             \
    template <>                                                         \
    void Talos::Machine::Visitor::accept<Talos::Bytecode::Syllable::N>( \
        Builder * B, Bytecode::Qualified<Bytecode::Syllable::N> * I)

#define TALOS_MM_MACHINE_UNIMPLEMENTED(N, ...)                          \
    template <>                                                         \
    void Talos::Machine::Visitor::accept<Talos::Bytecode::Syllable::N>( \
        Builder*, Bytecode::Qualified<Bytecode::Syllable::N>*) {        \
        $_ABORT("Unimplemented Machine::Visitor::accept<" #N ">");      \
    }

//  NAMESPACES  //

namespace Talos::Machine::Visitor {

    /**
     * @brief Handles accepting build requests.
     * @param builder                   Machine builder.
     * @param instruction               Qualified instruction.
     */
    template <Bytecode::Syllable S>
    void accept(Builder* builder, Bytecode::Qualified<S>* instruction);

    // ensure all the incoming instructions have been defined
#define TALOS_XX_SYLLABLE_BASE(N, ...) \
    template <>                        \
    void accept(Builder* builder, Bytecode::Qualified<Bytecode::Syllable::N>* instruction);
#include "talos/bytecode/_defines/syllables.def"

    /**
     * @brief Delegates incoming instructions.
     * @param builder                   Machine builder.
     * @param instruction               Bytecode instruction.
     */
    inline constexpr void accept(Builder* builder, Bytecode::Instruction* instruction) {
        switch (instruction->syllable()) {
#define TALOS_XX_SYLLABLE_BASE(N, ...) \
    case Bytecode::Syllable::N: accept(builder, instruction->cast<Bytecode::Syllable::N>()); break;
#include "talos/bytecode/_defines/syllables.def"
            default: $_ABORT("Unknown bytecode instruction: {0}", static_cast<uint8_t>(instruction->syllable())); break;
        }
    }

}  // namespace Talos::Machine::Visitor

#endif
