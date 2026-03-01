#ifndef _FORGE_FORWARD_BYTECODE_HPP
#define _FORGE_FORWARD_BYTECODE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(class Loop, Forge::Bytecode)
$_FWD(class Block, Forge::Bytecode)
$_FWD(class Binder, Forge::Bytecode)
$_FWD(struct Label, Forge::Bytecode)
$_FWD(struct Index, Forge::Bytecode)
$_FWD(struct Shared, Forge::Bytecode)
$_FWD(class Invoker, Forge::Bytecode)
$_FWD(class Request, Forge::Bytecode)
$_FWD(struct Routine, Forge::Bytecode)
$_FWD(class Compiler, Forge::Bytecode)
$_FWD(class Allocator, Forge::Bytecode)
$_FWD(class Assembler, Forge::Bytecode)
$_FWD(class Optimizer, Forge::Bytecode)
$_FWD(struct Instruction, Forge::Bytecode)

/// Forward Definitions
$_FWD(enum class Syllable : uint8_t, Forge::Bytecode)
$_FWD(template <class...> struct Operands, Forge::Bytecode)

#endif
