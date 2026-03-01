#ifndef _FORGE_FORWARD_DYLIB_HPP
#define _FORGE_FORWARD_DYLIB_HPP

/// Forge Modules
#include "forge/object/instance.hpp"

/// Forward Declarations
$_FWD(class Addon, Forge::Dylib)
$_FWD(class Registry, Forge::Dylib)

/// Forward Definitions
$_FWD(using Exports = Object::Instance, Forge::Dylib)
$_FWD(using Loader = $::Functor::Unique<void(Runtime::Isolate*, Exports&)>, Forge::Dylib)

#endif
