#ifndef _TALOS_FORWARD_GLOBALS_HPP
#define _TALOS_FORWARD_GLOBALS_HPP

/// Talos Modules
#include "talos/forward/runtime.hpp"
#include "talos/forward/value.hpp"

/// Forward Declarations
$_FWD(Talos::Globals, class Each)
$_FWD(Talos::Globals, class Roots)
$_FWD(Talos::Globals, class Service)

/// Forward Definitions
$_FWD(Talos::Globals, using Callback = $::Functor::Shared<void(Value::Any&)>)
$_FWD(Talos::Globals, using Factory = $::Functor::Unique<Value::Any(Runtime::Isolate*)>)

#endif
