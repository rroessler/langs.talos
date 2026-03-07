/// Talos Modules
#include "talos/type/builder.hpp"

//  PUBLIC METHODS  //

$::Ptr::Shared<Talos::Type::Instance> Talos::Type::Prototype::instantiate() {
    auto self = as<Prototype>();
    $_ASSERT(self.get() == this);
    return $::New().shared<Instance>(self);
}

//  PRIVATE METHODS  //

Talos::Type::Erased Talos::Type::Prototype::m_infer(const Constraints& constraints) const {
    // clone the underlying instance firstly
    auto inferred = m_clone()->as<Prototype>();

    // we need to instantiate each of the classes base details
    if (m_super) inferred->m_super = m_super->infer(constraints);

    // allow inferring the underlying protocol as well
    inferred->m_protocol = m_protocol->infer(constraints)->as<Protocol>();

    // and return the inferred prototype as necessary now
    return inferred;
}

bool Talos::Type::Prototype::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // stop if the candidate is not a class type
    if (!candidate->is<Prototype>()) return false;

    // get the other candidate available now
    auto other = candidate->as<Prototype>();

    // attempt finding a suitable super-class instance
    while (other && !other->m_derived(m_shape)) {
        if (other->m_super->is<None>()) other = nullptr;
        else other = other->m_super->as<Prototype>();
    }

    // fail when there is no common super-class
    if (other == nullptr) return false;

    // validate against the constraints now
    const auto &is = this->constraints(), &os = other->constraints();

    // get the minimum number of arguments to suitably check against
    auto arity = std::min(is.size(), os.size());

    // check using covariance (although this will lead to unsoundness for now)
    for (size_t ii = 0; ii < arity; ++ii) {
        if (!is.at(ii)->unify(os.at(ii), constraints)) return false;
    }

    // should be suitably valid now
    return true;
}

void Talos::Type::Prototype::m_print($::Stream::Output& os) const { os << "class " << name(); }
