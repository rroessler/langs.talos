#ifndef _TALOS_FORWARD_BYTECODE_HPP
#define _TALOS_FORWARD_BYTECODE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(Talos::Bytecode, class Loop)
$_FWD(Talos::Bytecode, class Block)
$_FWD(Talos::Bytecode, class Binder)
$_FWD(Talos::Bytecode, struct Label)
$_FWD(Talos::Bytecode, struct Index)
$_FWD(Talos::Bytecode, struct Shared)
$_FWD(Talos::Bytecode, class Invoker)
$_FWD(Talos::Bytecode, class Request)
$_FWD(Talos::Bytecode, struct Routine)
$_FWD(Talos::Bytecode, class Compiler)
$_FWD(Talos::Bytecode, class Allocator)
$_FWD(Talos::Bytecode, class Assembler)
$_FWD(Talos::Bytecode, class Optimizer)
$_FWD(Talos::Bytecode, struct Instruction)

/// Forward Definitions
$_FWD(Talos::Bytecode, enum class Syllable : uint8_t)
$_FWD(Talos::Bytecode, template <class...> struct Operands)

#endif
