#ifndef _TALOS_FORWARD_ENGINE_HPP
#define _TALOS_FORWARD_ENGINE_HPP

/// Talos Includes
#include "talos/forward/function.hpp"
#include "talos/forward/register.hpp"
#include "talos/forward/runtime.hpp"

/// Forward Declarations
$_FWD(Talos::Engine, struct Frame)
$_FWD(Talos::Engine, class Exports)

/// Forward Definitions
$_FWD(Talos::Engine, using Args = Function::Args)
$_FWD(Talos::Engine, using Isolate = Runtime::Isolate)

#endif
