#ifndef _XASM_FORWARD_HOSTED_HPP
#define _XASM_FORWARD_HOSTED_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Definitions
$_FWD(using Label = asmjit::Label, XASM::Host)
$_FWD(using Immediate = asmjit::Imm, XASM::Host)
$_FWD(using Memory = asmjit::ujit::Mem, XASM::Host)
$_FWD(using Register = asmjit::ujit::Gp, XASM::Host)
$_FWD(using Double = asmjit::ujit::Vec, XASM::Host)

#endif
