#ifndef _XASM_FORWARD_HOSTED_HPP
#define _XASM_FORWARD_HOSTED_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(XASM::Host, using Label = asmjit::Label)
$_FWD(XASM::Host, using Immediate = asmjit::Imm)
$_FWD(XASM::Host, using Memory = asmjit::ujit::Mem)
$_FWD(XASM::Host, using Register = asmjit::ujit::Gp)
$_FWD(XASM::Host, using Double = asmjit::ujit::Vec)

#endif
