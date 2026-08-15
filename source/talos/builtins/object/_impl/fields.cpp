/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Member::View Talos::Builtins::Wrapper<Talos::Object::Instance>::m_attribute(
    const Object::Instance &self, const Value::Symbol &symbol
) {
  const auto &fields = self.fields(); // prepare base
  auto iter = fields.find(symbol), cend = fields.cend();
  return iter == cend ? nullptr : iter->second.get();
}
