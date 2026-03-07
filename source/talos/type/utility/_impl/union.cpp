/// Talos Modules
#include "talos/type/builder.hpp"

//  PRIVATE METHODS  //

Talos::Type::Erased Talos::Type::Union::m_infer(const Constraints& constraints) const {
    // prepare the base union to be inherited
    Erased result = Builder::never();

    // iterate over the available children now
    for (const auto& element : m_elements) {
        result = Builder::merge(result, element->infer(constraints));
        if (result->is<Any>()) break;  // stop early if possible to do
    }

    // return the merged typing now
    return result;
}

bool Talos::Type::Union::m_unify(const Erased& candidate, const Constraints& constraints) const {
    // attempt getting the other items children as necessary now
    auto elements = candidate->is<Union>() ? candidate->as<Union>()->m_elements : std::vector({ candidate });

    // prepare a predicate to be used
    auto predicate = [this, constraints](const Erased& other) -> bool {
        auto check = [other, constraints](const Erased& element) { return element->unify(other, constraints); };
        return std::ranges::any_of(m_elements, check);  // and attempt checking now via the reference check
    };

    // ensure our children fulfill the candidates children
    return std::ranges::all_of(elements, predicate);
}
