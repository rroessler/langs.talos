#ifndef _FORGE_BYTECODE_SYLLABLE_HPP
#define _FORGE_BYTECODE_SYLLABLE_HPP

/// Forge Modules
#include "forge/bytecode/allocator.hpp"
#include "forge/bytecode/label.hpp"

namespace Forge::Bytecode {

    /// @brief All available bytecode syllables.
    enum class Syllable : uint8_t {
#define FORGE_XX_SYLLABLE_BASE(N, ...) N,
#include "forge/bytecode/_defines/syllables.def"
    };

    /// @brief Ensures that the maximum syllable does not exceed 1-byte in size.
    static_assert(static_cast<size_t>(Syllable::EXEC_INVALID) < UINT8_MAX, "Exceeded maximum opcode count");

}  // namespace Forge::Bytecode

#endif
