/// Talos Includes
#include "talos/value/void.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Value::Void>::m_globals(Isolate *) { return Value::Void(); }
