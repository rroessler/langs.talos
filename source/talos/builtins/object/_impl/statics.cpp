/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Object::Instance>::m_globals(Isolate *, const Object::Class &self) {
  return self;
}
