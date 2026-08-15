#ifndef _TALOS_VARIABLE_UPVALUES_HPP
#define _TALOS_VARIABLE_UPVALUES_HPP

/// Talos Includes
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/label.hpp"
#include "talos/forward/variable.hpp"

namespace Talos::Variable {

/// @brief Variable Lookup Result.
struct Upvalue {
  Bytecode::Index depth; // Frame depth away.
  Register::Slot slot;   // Index of upvalue.
};

} // namespace Talos::Variable

#endif
