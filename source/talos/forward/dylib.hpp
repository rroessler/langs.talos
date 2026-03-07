#ifndef _TALOS_FORWARD_DYLIB_HPP
#define _TALOS_FORWARD_DYLIB_HPP

/// Talos Modules
#include "talos/object/instance.hpp"

/// Forward Declarations
$_FWD(class Addon, Talos::Dylib)
$_FWD(class Registry, Talos::Dylib)

/// Forward Definitions
$_FWD(using Exports = Object::Instance, Talos::Dylib)
$_FWD(using Loader = $::Functor::Unique<void(Runtime::Isolate*, Exports&)>, Talos::Dylib)

#endif
