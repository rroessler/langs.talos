/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Value::Boolean>::m_attribute(const Value::Boolean &, const Value::Symbol &) {
  return nullptr;
}
