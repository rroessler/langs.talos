#ifndef _XASM_FORWARD_FUNCTION_HPP
#define _XASM_FORWARD_FUNCTION_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(using Node = asmjit::FuncNode, XASM::Function)
$_FWD(using Callee = asmjit::InvokeNode, XASM::Function)
$_FWD(using Signature = asmjit::FuncSignature, XASM::Function)

#endif
