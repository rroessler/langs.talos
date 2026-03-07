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
    auto value = target->infer(constraints)->apply(Operator::Kind::ITER);
    return value->is<Unset>() ? Builder::never() : Builder::iterator(value);
}
