/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Object::Class>::m_globals(Isolate *, const Object::Class &self) {
  return self; // and return the resulting instance
}
