#ifndef _TALOS_MACHINE_VISITOR_HPP
#define _TALOS_MACHINE_VISITOR_HPP

/// Talos Includes
#include "talos/machine/builder.hpp"

namespace Talos::Machine::Visitor {

/**
 * @brief Handles accepting build requests.
 * @param builder                   Machine builder.
 * @param instruction               Qualified instruction.
 */
template <Bytecode::Glyph::Encoded G> void accept(Builder *builder, const Bytecode::Qualified<G> *instruction);

// ensure all the incoming instructions have been defined
#define TALOS_XX_GLYPH_BASE(N, ...)                                                                      \
  template <> void accept(Builder *builder, const Bytecode::Qualified<Bytecode::Glyph::N> *instruction);
#include "talos/bytecode/_defines/glyphs.def"

/**
 * @brief Delegates incoming instructions.
 * @param builder                   Machine builder.
 * @param instruction               Bytecode instruction.
 */
inline constexpr void accept(Builder *builder, const Bytecode::Instruction *instruction) {
  switch (instruction->glyph().encoded()) {
#define TALOS_XX_GLYPH_BASE(N, ...)                                                         \
  case Bytecode::Glyph::N: accept(builder, instruction->cast<Bytecode::Glyph::N>()); break;
#include "talos/bytecode/_defines/glyphs.def"
  default: $_ABORT("Unknown bytecode instruction: {0}", instruction->label()); break;
  }
}

} // namespace Talos::Machine::Visitor

#endif
