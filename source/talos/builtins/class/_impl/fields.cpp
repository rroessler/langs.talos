/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Object::Class>::m_attribute(const Object::Class &self, const Value::Symbol &symbol) {
  const auto &statics = self.statics(); // prepare base
  auto iter = statics.find(symbol), cend = statics.cend();
  return iter == cend ? nullptr : iter->second.get();
}
