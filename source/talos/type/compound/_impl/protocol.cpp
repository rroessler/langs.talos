/// Talos Modules
#include "talos/type/builder.hpp"

//  PRIVATE METHODS  //

Talos::Type::Erased Talos::Type::Protocol::m_infer(const Constraints& constraints) const {
    // prepare an inferred instance now
    auto inferred = m_clone()->as<Protocol>();

    // infer all the constraints to be bound
    for (const auto& [ii, c] : $::Each(m_constraints)) inferred->m_constraints[ii] = c->infer(constraints);

    // and return the resulting inferred instance now
    return inferred;
}

bool Talos::Type::Protocol::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // iterably ensure that every field has been fulfilled
    for (const auto& [name, entity] : m_fields.view(this, constraints)) {
        auto other = candidate->lookup(name);  // get the other value now
        if (!other.value()->unify(entity.value(), constraints)) return false;
    }

    // should be a success as we got through all the fields
    return true;
}

void Talos::Type::Protocol::m_print($::Stream::Output& os) const {
    // determine a suitably typing to be used now
    if (m_name.size()) os << m_name;
    else if (m_fallback == nullptr) os << "{}";
    else if (m_fallback->is<Any>()) os << "Object";
    else os << "Record[" << *m_fallback << ']';

    // append the constraints used on the incoming object now
    if (m_constraints.size()) os << '[' << $::Convert::join(m_constraints) << ']';
}
