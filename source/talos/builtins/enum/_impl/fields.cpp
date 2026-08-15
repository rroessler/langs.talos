/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Object::Enum>::m_attribute(const Object::Enum &self, const Value::Symbol &symbol) {
  auto *variant = self.resolve(symbol); // find
  return variant ? variant->value.get() : nullptr;
}
