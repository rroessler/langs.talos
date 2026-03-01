/// Forge Modules
#include "forge/bytecode/instruction.hpp"

//  PRIVATE METHODS  //

void Forge::Bytecode::Instruction::m_print($::Stream::Output& os, const Instruction& self) {
    // print the baseline name to begin with
    os << self.name();

    // attempt printing each available operand now
    switch (self.syllable()) {
#define FORGE_XX_SYLLABLE_BASE(N, ...) \
    case Syllable::N: self.cast<Syllable::N>()->m_print(os); break;
#include "forge/bytecode/_defines/syllables.def"
    }
}
