/// Forge Modules
#include "forge/type/builder.hpp"

//  PUBLIC METHODS  //

Forge::Type::Entity Forge::Type::Tagged::lookup(const $::String::View&) const { return Entity(); }

Forge::Type::Erased Forge::Type::Tagged::apply(Operator::Kind kind) const {
    switch (kind) {
        case Operator::Kind::NOT: return Builder::boolean();
        default: return Builder::unset();  // unknown operator
    }
}

Forge::Type::Erased Forge::Type::Tagged::apply(Operator::Kind kind, const Erased& right) const {
    switch (kind) {
        // prepare the kinds to be used now
        case Operator::Kind::EQ: $_FALLTHROUGH;
        case Operator::Kind::NE: $_FALLTHROUGH;
        case Operator::Kind::LOR: $_FALLTHROUGH;
        case Operator::Kind::LAND: return Builder::boolean();

        // assignments must be valid unifications
        case Operator::Kind::ASGN: return unify(right) ? right : Builder::unset();

        // nullish coalescing allows us to return ourselves or the right-most
        case Operator::Kind::COAL: return Builder::coalesce(const_cast<Tagged*>(this)->as<Tagged>(), right);

        // should default to be an unknown value here
        default: return Builder::unset();
    }
}

bool Forge::Type::Tagged::unify(const Erased& candidate, const Constraints& constraints) const {
    // handle some immediate conditions that may occur
    if (this == candidate.get()) return true;

    // check against parameters and generics now
    if (candidate->is<Parameter>()) return m_unify(candidate->as<Parameter>(), constraints);
    if (candidate->is<Generic>() && !is<Generic>()) return m_unify(candidate->as<Generic>(), constraints);

    // bypass simple conditions (such as "Any" and "Never" types)
    if (!is<Parameter>() && (candidate->is<Any>() || candidate->lattice().bottom())) return true;

    // otherwise try the baseline unification routine
    return m_unify(candidate, constraints);
}

//  PRIVATE METHODS  //

bool Forge::Type::Tagged::m_unify(const $::Ptr::Shared<Generic>& generic, const Constraints& constraints) const {
    // prepare the outgoing constraints to be used now
    auto outgoing = constraints == nullptr ? $::New().shared<Constraints::element_type>() : constraints;

    // prepare the distinct typings to be used now
    auto distinct = std::vector<Erased>();

    // emplace all the generic parameters to be inferred
    for (const auto& parameter : generic->parameters()) {
        auto constraint = Builder::constraint(*parameter);  // clone the constraint to use
        distinct.emplace_back(constraint), (*outgoing)[constraint.get()] = Builder::unset();
    }

    // and finally attempt unification with the distinct parameters now
    return m_unify(generic->instantiate(distinct), outgoing);
}

bool Forge::Type::Tagged::m_unify(const $::Ptr::Shared<Parameter>& parameter, const Constraints& constraints) const {
    // ignore if there are no constraints available
    if (constraints == nullptr) return m_unify(parameter->as<Tagged>(), constraints);

    auto iter = constraints->find(parameter.get());  // check for bound, and allow binding now
    if (iter == constraints->cend()) return m_unify(parameter->as<Tagged>(), constraints);

    // check if the parameter is being inferred, so clone the type now
    if (iter->second->is<Unset>()) return (*constraints)[parameter.get()] = m_clone(), true;

    // otherwise we check for a suitably match now
    return iter->second.get() == this || m_unify(iter->second, constraints);
}

void Forge::Type::Tagged::m_print($::Stream::Output& os, const Tagged& self) { self.m_print(os); }
