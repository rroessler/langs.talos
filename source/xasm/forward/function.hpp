#ifndef _XASM_FORWARD_FUNCTION_HPP
#define _XASM_FORWARD_FUNCTION_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(XASM::Function, using Node = asmjit::FuncNode)
$_FWD(XASM::Function, using Callee = asmjit::InvokeNode)
$_FWD(XASM::Function, using Signature = asmjit::FuncSignature)

#endif
