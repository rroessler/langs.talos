#ifndef _FORGE_FUNCTION_CALLBACK_HPP
#define _FORGE_FUNCTION_CALLBACK_HPP

/// Forge Modules
#include "forge/forward/engine.hpp"
#include "forge/forward/runtime.hpp"
#include "forge/function/arguments.hpp"

/// Forward Definitions
$_FWD(using Callback = Value::Any (*)(Runtime::Isolate*, const Arguments&), Forge::Function);

#endif
