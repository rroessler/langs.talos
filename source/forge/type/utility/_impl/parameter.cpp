/// Forge Modules
#include "forge/type/builder.hpp"

//  PRIVATE METHODS  //

Forge::Type::Erased Forge::Type::Parameter::m_infer(const Constraints& constraints) const {
    if (constraints == nullptr) return m_clone();
    if (!constraints->contains(this)) return m_clone();
    return constraints->at(this);  // found so return
}

bool Forge::Type::Parameter::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // ignore if there are no constraints available
    if (constraints == nullptr) return m_extends->unify(candidate);

    // check if this parameter exist in the available constraints
    auto iter = constraints->find(this);
    if (iter == constraints->cend()) return false;

    // check if the parameter is being inferred, so clone the type now
    if (iter->second->is<Unset>()) {
        if (!m_extends->unify(candidate)) return false;
        return (*constraints)[this] = candidate, true;
    }

    // otherwise we check for a suitable match now
    return iter->second.get() == this || iter->second->unify(candidate, constraints);
}
