#ifndef _TALOS_FORWARD_BYTECODE_HPP
#define _TALOS_FORWARD_BYTECODE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(class Loop, Talos::Bytecode)
$_FWD(class Block, Talos::Bytecode)
$_FWD(class Binder, Talos::Bytecode)
$_FWD(struct Label, Talos::Bytecode)
$_FWD(struct Index, Talos::Bytecode)
$_FWD(struct Shared, Talos::Bytecode)
$_FWD(class Invoker, Talos::Bytecode)
$_FWD(class Request, Talos::Bytecode)
$_FWD(struct Routine, Talos::Bytecode)
$_FWD(class Compiler, Talos::Bytecode)
$_FWD(class Allocator, Talos::Bytecode)
$_FWD(class Assembler, Talos::Bytecode)
$_FWD(class Optimizer, Talos::Bytecode)
$_FWD(struct Instruction, Talos::Bytecode)

/// Forward Definitions
$_FWD(enum class Syllable : uint8_t, Talos::Bytecode)
$_FWD(template <class...> struct Operands, Talos::Bytecode)

#endif
