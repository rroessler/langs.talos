#ifndef _TALOS_FUNCTION_CALLBACK_HPP
#define _TALOS_FUNCTION_CALLBACK_HPP

/// Talos Modules
#include "talos/forward/engine.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/function/arguments.hpp"

/// Forward Definitions
$_FWD(using Callback = Value::Any (*)(Runtime::Isolate*, const Arguments&), Talos::Function);

#endif
