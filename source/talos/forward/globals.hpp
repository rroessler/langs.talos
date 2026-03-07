#ifndef _TALOS_FORWARD_GLOBALS_HPP
#define _TALOS_FORWARD_GLOBALS_HPP

/// Talos Modules
#include "talos/forward/runtime.hpp"
#include "talos/forward/value.hpp"

/// Forward Declarations
$_FWD(class Each, Talos::Globals)
$_FWD(class Roots, Talos::Globals)
$_FWD(class Service, Talos::Globals)

/// Forward Definitions
$_FWD(using Callback = $::Functor::Shared<void(Value::Any&)>, Talos::Globals)
$_FWD(using Factory = $::Functor::Unique<Value::Any(Runtime::Isolate*)>, Talos::Globals)

#endif
