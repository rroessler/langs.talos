#ifndef _FORGE_FORWARD_ENGINE_HPP
#define _FORGE_FORWARD_ENGINE_HPP

/// Forge Modules
#include "forge/forward/runtime.hpp"

/// Forward Declarations
$_FWD(struct Call, Forge::Engine)
$_FWD(struct Frame, Forge::Engine)
$_FWD(class Exports, Forge::Engine)
$_FWD(class Dispatch, Forge::Engine)
$_FWD(struct Register, Forge::Engine)
$_FWD(struct Accumulator, Forge::Engine)

/// Forward Definitions
$_FWD(using Isolate = Runtime::Isolate, Forge::Engine)

#endif
