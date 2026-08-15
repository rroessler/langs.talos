#ifndef _XASM_FORWARD_COMPILER_HPP
#define _XASM_FORWARD_COMPILER_HPP

/// Vendor Includes
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(XASM::Compiler, using Arena = asmjit::CodeHolder)
$_FWD(XASM::Compiler, using Backend = asmjit::host::Compiler)
$_FWD(XASM::Compiler, using Universal = asmjit::ujit::UniCompiler)

#endif
