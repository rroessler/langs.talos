#ifndef _FORGE_VARIABLE_UPVALUES_HPP
#define _FORGE_VARIABLE_UPVALUES_HPP

/// Forge Modules
#include "forge/bytecode/allocator.hpp"
#include "forge/bytecode/label.hpp"
#include "forge/forward/variable.hpp"

namespace Forge::Variable {

    /// @brief Variable Lookup Result.
    struct Upvalue {
        Bytecode::Index depth;    // Frame depth away.
        Bytecode::Register slot;  // Index of upvalue.
    };

}  // namespace Forge::Variable

#endif
