/// Forge Modules
#include "forge/type/builder.hpp"

/// Value Modules
#include "forge/value/_inline/value.ipp"

//  PUBLIC METHODS  //

Forge::Type::Entity Forge::Type::Callable::lookup(const $::String::View& field) const {
    if (field != "bind") return Builtins::Proxy<Function::Dynamic>::prototype()->instantiate()->lookup(field);
    else return { Builder::function(m_clone()->as<Callable>(), Builder::arguments(Builder::any())) };
}

//  PRIVATE METHODS  //

Forge::Type::Erased Forge::Type::Callable::m_infer(const Constraints& constraints) const {
    // prepare the cloned callable instance
    auto callable = m_clone()->as<Callable>();

    // ignore if not given any generics
    if (constraints == nullptr) return callable;

    // otherwise rebuild the parameters and return value
    callable->returns() = m_returns->infer(constraints);

    // instantiate all the parameters
    for (const auto& [ii, p] : $::Each(m_parameters)) callable->m_parameters[ii] = p.infer(constraints);

    // and return the resulting callable instance now
    return callable;
}

bool Forge::Type::Callable::m_unify(const Erased& candidate, const Constraints& constraints) const {
    auto other = Builder::resolve<Callable>(candidate);
    if (other == nullptr) return false;  // failed here

    // ensure we validate our size of parameters before continuing
    if (arity() > other->arity() || adicity() < other->adicity()) return false;

    auto maximum = m_parameters.size();  // prepare details
    auto spread = packed() ? m_parameters.back() : Entity();

    // stop if any of the parameters are invalid
    for (const auto& [ii, right] : $::Each(other->m_parameters)) {
        const auto& left = ii < maximum ? m_parameters.at(ii) : spread;
        $_ASSERT(left.opaque() && right.opaque(), "Parameters should be opaque");
        if (!left.value()->unify(right.value(), constraints)) return false;
    }

    // finally ensures the return value is also the same
    return m_returns->unify(other->m_returns, constraints);
}

void Forge::Type::Callable::m_print($::Stream::Output& os) const {
    // prepare the transformation predicate to be used
    constexpr auto predicate = [](const Entity& entity) {
        return fmt::format("{0}", *entity.value()) + (entity.optional() ? "?" : "");
    };

    // build our parameters to be printed as necessary
    auto parameters = $::Ranges::To(m_parameters | std::views::transform(predicate));

    // prepare the packed details to be used now
    auto spread = packed() ? m_parameters.back().value() : nullptr;
    if (spread != nullptr) parameters.pop_back();  // pop spread now

    // get the current emptiness to be used
    auto empty = parameters.empty();
    auto parens = !empty || spread;

    // test for the "Any" function instance
    if (spread && empty && spread->is<Any>() && m_returns->is<Any>()) {
        os << Value::Proxy<Function::Dynamic>::name();
    } else {
        os << "fn" << (parens ? " (" : "") << $::Convert::join(parameters);
        if (spread) os << (empty ? "" : ", ") << "..." << *spread;
        os << (parens ? ")" : "") << " -> " << *m_returns;
    }
}
