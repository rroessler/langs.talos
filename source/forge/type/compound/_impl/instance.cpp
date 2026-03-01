/// Forge Modules
#include "forge/type/builder.hpp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  PUBLIC METHODS  //

$::Ternary Forge::Type::Instance::truthiness() const noexcept {
    auto type = lattice();  // prepare type
    auto truthy = type.test(Fact::IS_TRUTHY);
    auto falsey = type.test(Fact::IS_FALSEY);
    if (truthy == falsey) return $::Unknown();
    else return $::Ternary(truthy);  // known
}

Forge::Type::Lattice Forge::Type::Instance::lattice() const noexcept {
    // ensure always correct for anonymous instances
    if (m_prototype == nullptr) return Fact::OBJ_ANY;

    // otherwise check against the incoming prototype
    switch (m_prototype->m_base()) {
        case Shape::Lookup<Value::Symbol>(): return Fact::SYM_ANY;
        case Shape::Lookup<Value::Boolean>(): return Fact::BIT_ANY;
        case Shape::Lookup<Number::Tagged>(): return Fact::NUM_ANY;
        case Shape::Lookup<String::Dynamic>(): return Fact::STR_ANY;
        default: return Fact::OBJ_ANY;  // could be any object value
    }
}

Forge::Type::Entity Forge::Type::Instance::lookup(const $::String::View& field) const {
    return m_prototype ? m_prototype->m_lookup(field) : Entity(Builder::any());
}

Forge::Type::Erased Forge::Type::Instance::apply(Operator::Kind kind) const { return apply(kind, nullptr); }
Forge::Type::Erased Forge::Type::Instance::apply(Operator::Kind kind, const Erased& right) const {
    // ignore if there is no valid protocol at all
    if (m_prototype == nullptr) return Builder::any();

    // prepare the incoming parameters to be used
    auto& operators = m_prototype->m_operators;
    auto* protocol = m_prototype->m_protocol.get();

    auto result = operators == nullptr ? Builder::unset() : operators(protocol, kind, right);
    return result->is<Unset>() ? right ? Abstract::apply(kind, right) : Abstract::apply(kind) : result;
}

//  PRIVATE METHODS  //

Forge::Type::Erased Forge::Type::Instance::m_infer(const Constraints& constraints) const {
    if (m_prototype == nullptr) return m_clone();  // simple clone of the value
    return m_prototype->infer(constraints)->as<Prototype>()->instantiate();
}

bool Forge::Type::Instance::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // attempt resolving a suitable prototype
    auto other = Builder::resolve<Prototype>(candidate);

    if (other == nullptr) return false;       // failed to find a parent class
    if (m_prototype == nullptr) return true;  // pass all generic objects now

    // otherwise we check against the incoming class
    return m_prototype->unify(other, constraints);
}

void Forge::Type::Instance::m_print($::Stream::Output& os) const {
    // do a regular print if there is no prototype available
    if (!m_prototype) return void(os << Value::Proxy<Object::Instance>::name());

    // otherwise we want to print the base-class name
    os << m_prototype->name();
    if (m_prototype->constraints().empty()) return;
    os << '[' << $::Convert::join(m_prototype->constraints()) << ']';
}
