#ifndef _XASM_FORWARD_RUNTIME_HPP
#define _XASM_FORWARD_RUNTIME_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(XASM::Runtime, class Context)

/// Forward Definitions
$_FWD(XASM::Runtime, using Hints = asmjit::CpuHints)
$_FWD(XASM::Runtime, using Target = asmjit::JitRuntime)
$_FWD(XASM::Runtime, using Logger = asmjit::StringLogger)
$_FWD(XASM::Runtime, using Features = asmjit::CpuFeatures)
$_FWD(XASM::Runtime, using Environment = asmjit::Environment)

#endif
