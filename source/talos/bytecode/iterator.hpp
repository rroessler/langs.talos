#ifndef _TALOS_BYTECODE_ITERATOR_HPP
#define _TALOS_BYTECODE_ITERATOR_HPP

/// Talos Includes
#include "talos/bytecode/instruction.hpp"
#include "talos/image/slice.hpp"

namespace Talos::Bytecode {

/**
 * @brief Bytecode Iterator Span.
 * @param slice                 Bytecode slice.
 */
static inline constexpr std::span<const Instruction> Iterator(const Image::Slice &slice) {
  return {reinterpret_cast<const Instruction *>(slice.address()), slice.size() / Width};
}

} // namespace Talos::Bytecode

#endif
