#ifndef _XASM_FORWARD_COMPILER_HPP
#define _XASM_FORWARD_COMPILER_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(using Arena = asmjit::CodeHolder, XASM::Compiler)
$_FWD(using Backend = asmjit::host::Compiler, XASM::Compiler)
$_FWD(using Universal = asmjit::ujit::UniCompiler, XASM::Compiler)

#endif
