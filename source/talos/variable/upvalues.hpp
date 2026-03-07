#ifndef _TALOS_VARIABLE_UPVALUES_HPP
#define _TALOS_VARIABLE_UPVALUES_HPP

/// Talos Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/label.hpp"
#include "talos/forward/variable.hpp"

namespace Talos::Variable {

    /// @brief Variable Lookup Result.
    struct Upvalue {
        Bytecode::Index depth;    // Frame depth away.
        Bytecode::Register slot;  // Index of upvalue.
    };

}  // namespace Talos::Variable

#endif
