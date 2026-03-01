#ifndef _XASM_FORWARD_RUNTIME_HPP
#define _XASM_FORWARD_RUNTIME_HPP

/// Vendor Modules
#include <asmjit/ujit.h>
#include <xtdlib/xtdlib.hpp>

/// Forward Declarations
$_FWD(class Context, XASM::Runtime)

/// Forward Definitions
$_FWD(using Hints = asmjit::CpuHints, XASM::Runtime)
$_FWD(using Target = asmjit::JitRuntime, XASM::Runtime)
$_FWD(using Logger = asmjit::StringLogger, XASM::Runtime)
$_FWD(using Features = asmjit::CpuFeatures, XASM::Runtime)
$_FWD(using Environment = asmjit::Environment, XASM::Runtime)

#endif
