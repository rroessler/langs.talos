/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Value::Void)::m_globals(Runtime::Isolate*) { return Value::Void(); }
