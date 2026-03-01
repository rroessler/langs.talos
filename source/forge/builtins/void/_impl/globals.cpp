/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Value::Void)::m_globals(Runtime::Isolate*) { return Value::Void(); }
