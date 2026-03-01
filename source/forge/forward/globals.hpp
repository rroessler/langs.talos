#ifndef _FORGE_FORWARD_GLOBALS_HPP
#define _FORGE_FORWARD_GLOBALS_HPP

/// Forge Modules
#include "forge/forward/runtime.hpp"
#include "forge/forward/value.hpp"

/// Forward Declarations
$_FWD(class Each, Forge::Globals)
$_FWD(class Roots, Forge::Globals)
$_FWD(class Service, Forge::Globals)

/// Forward Definitions
$_FWD(using Callback = $::Functor::Shared<void(Value::Any&)>, Forge::Globals)
$_FWD(using Factory = $::Functor::Unique<Value::Any(Runtime::Isolate*)>, Forge::Globals)

#endif
