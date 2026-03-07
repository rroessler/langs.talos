#ifndef _TALOS_FORWARD_ENGINE_HPP
#define _TALOS_FORWARD_ENGINE_HPP

/// Talos Modules
#include "talos/forward/runtime.hpp"

/// Forward Declarations
$_FWD(struct Call, Talos::Engine)
$_FWD(struct Frame, Talos::Engine)
$_FWD(class Exports, Talos::Engine)
$_FWD(class Dispatch, Talos::Engine)
$_FWD(struct Register, Talos::Engine)
$_FWD(struct Accumulator, Talos::Engine)

/// Forward Definitions
$_FWD(using Isolate = Runtime::Isolate, Talos::Engine)

#endif
