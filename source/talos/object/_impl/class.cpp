/// Talos Includes
#include "talos/object/class.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Object::Class::m_yield(const Class &self, Globals::Each &yield) {
  // get the underlying attributes
  auto *attributes = self.m_wrapper();

  // emplace the baseline details
  yield(attributes->name);
  yield(attributes->parent);

  // yield all the underlying member references as necessary now
  for (const auto &member : attributes->statics | std::views::values) yield(member->reference());
}
