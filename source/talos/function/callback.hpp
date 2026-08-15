#ifndef _TALOS_FUNCTION_CALLBACK_HPP
#define _TALOS_FUNCTION_CALLBACK_HPP

/// Talos Includes
#include "talos/forward/engine.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/function/args.hpp"

/// Forward Definitions
$_FWD(Talos::Function, using Callback = Value::Any (*)(Runtime::Isolate *, const Args &));

#endif
