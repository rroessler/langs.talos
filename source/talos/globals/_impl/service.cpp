/// Talos Modules
#include "talos/globals/service.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Globals::Service::Service() {
#define X(T, ...)                                         \
    if (auto&& factory = Builtins::Proxy<T>::m_globals()) \
        m_factories.emplace(Builtins::Proxy<T>::name(), std::move(factory));
    TALOS_XX_BUILTINS_LIST(X)
#undef X

    // declare globals as accessible to roots now
    m_roots->bind([this](const Each& yield) {
        for (auto& value : m_values | std::views::values) yield(value);
        for (auto& value : m_internal | std::views::values) yield(value);
    });
}
