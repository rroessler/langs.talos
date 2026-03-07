#ifndef _TALOS_BYTECODE_SYLLABLE_HPP
#define _TALOS_BYTECODE_SYLLABLE_HPP

/// Talos Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/label.hpp"

namespace Talos::Bytecode {

    /// @brief All available bytecode syllables.
    enum class Syllable : uint8_t {
#define TALOS_XX_SYLLABLE_BASE(N, ...) N,
#include "talos/bytecode/_defines/syllables.def"
    };

    /// @brief Ensures that the maximum syllable does not exceed 1-byte in size.
    static_assert(static_cast<size_t>(Syllable::EXEC_INVALID) < UINT8_MAX, "Exceeded maximum opcode count");

}  // namespace Talos::Bytecode

#endif
