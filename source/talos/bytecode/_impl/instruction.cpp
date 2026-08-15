/// Talos Modules
#include "talos/bytecode/instruction.hpp"

//  PRIVATE METHODS  //

void Talos::Bytecode::Instruction::m_print(std::ostream &os, const Instruction &self) {
  // print the baseline name to begin with
  os << self.label();

  // attempt printing each available operand now
  switch (self.glyph().encoded()) {
#define TALOS_XX_GLYPH_BASE(N, ...)                         \
  case Glyph::N: self.cast<Glyph::N>()->m_print(os); break;
#include "talos/bytecode/_defines/glyphs.def"
  }
}
