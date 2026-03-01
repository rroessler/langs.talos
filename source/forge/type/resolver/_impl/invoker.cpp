/// Forge Modules
#include "forge/type/builder.hpp"

//  OPERATOR METHODS  //

Forge::Type::Erased Forge::Type::Utility::Invoker::operator()(
    const Erased& target, const Constraints& constraints) const noexcept {
    // if we have no constraints, then we try binding the target typing
    if (constraints == nullptr) return m_bind(target);

    // attempt resolving the underlying instance now
    auto instantiated = target->infer(constraints);
    if (instantiated->is<Any>()) return Builder::any();
    if (!instantiated->is<Callable>()) return Builder::unset();

    // attempt converting the incoming function now
    auto callable = instantiated->as<Callable>();

    // prepare the return value and parameters
    auto returns = m_returns(callable);
    auto parameters = callable->parameters();

    // rebuild the parameters to include the callable itself
    parameters.emplace(parameters.begin(), callable);

    // and reconstruct the resulting callable instance now
    return callable->packed() ? Builder::variadic(returns, parameters) : Builder::function(returns, parameters);
}

//  PRIVATE METHODS  //

/**
 * @brief Handles binding function parameters.
 * @param target                Target to bind.
 */
Forge::Type::Erased Forge::Type::Utility::Invoker::m_bind(const Erased& target) const noexcept {
    return Builder::variadic(Builder::any(), Builder::arguments(target, Builder::any()));
}

/**
 * @brief Handles resolving return-values.
 * @param callable              Callable to resolve.
 */
Forge::Type::Erased Forge::Type::Utility::Invoker::m_returns(const $::Ptr::Shared<Callable>& callable) const noexcept {
    if (!m_async) return callable->returns();  // do not asyncify
    return Builder::future(Builder::awaited(callable->returns()));
}
