/// Type Includes
#include "talos/type/_inline/type.ipp"

//  OPERATOR METHODS  //

Talos::Type::Erased
Talos::Type::Utility::Loopable::operator()(const Erased &target, Constraints *constraints) const noexcept {
  return m_resolve(target, constraints);
}

//  PRIVATE METHODS  //

Talos::Type::Erased
Talos::Type::Utility::Loopable::m_resolve(const Erased &target, Constraints *constraints) const noexcept {
  auto inferred = target->infer(constraints);
  auto value = inferred->apply(Operator::Kind::ITER);
  if (value->is<Unset>()) return New::never();
  return New::iterator(value); // valid iterator
}
