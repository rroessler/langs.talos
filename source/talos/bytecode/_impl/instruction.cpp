/// Talos Modules
#include "talos/bytecode/instruction.hpp"

//  PRIVATE METHODS  //

void Talos::Bytecode::Instruction::m_print($::Stream::Output& os, const Instruction& self) {
    // print the baseline name to begin with
    os << self.name();

    // attempt printing each available operand now
    switch (self.syllable()) {
#define TALOS_XX_SYLLABLE_BASE(N, ...) \
    case Syllable::N: self.cast<Syllable::N>()->m_print(os); break;
#include "talos/bytecode/_defines/syllables.def"
    }
}
