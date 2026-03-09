#ifndef _TALOS_FORWARD_DYLIB_HPP
#define _TALOS_FORWARD_DYLIB_HPP

/// Talos Modules
#include "talos/object/instance.hpp"

/// Forward Declarations
$_FWD(Talos::Dylib, class Addon)
$_FWD(Talos::Dylib, class Registry)

/// Forward Definitions
$_FWD(Talos::Dylib, using Exports = Object::Instance)
$_FWD(Talos::Dylib, using Loader = $::Functor::Unique<void(Runtime::Isolate*, Exports&)>)

#endif
