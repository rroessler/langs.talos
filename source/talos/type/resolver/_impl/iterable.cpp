/// Talos Modules
#include "talos/type/builder.hpp"

//  OPERATOR METHODS  //

Talos::Type::Erased Talos::Type::Utility::Iterable::operator()(
    const Erased& target, const Constraints& constraints) const noexcept {
    return m_resolve(target, constraints);
}

//  PRIVATE METHODS  //

Talos::Type::Erased Talos::Type::Utility::Iterable::m_resolve(
    const Erased& target, const Constraints& constraints) const noexcept {
    auto inferred = target->infer(constraints);
    auto value = inferred->apply(Operator::Kind::ITER);
    if (value->is<Unset>()) return Builder::never();
    return Builder::iterator(value);  // valid iterator
}
