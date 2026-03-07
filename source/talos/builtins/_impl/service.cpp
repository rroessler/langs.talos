/// Talos Modules
#include "talos/builtins/service.hpp"
#include "talos/runtime/container.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Builtins::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Builtins::Service::Service(XI::Container* services) :
    m_globals(services->when<Globals::Service>()), m_types($::New().unique<Type::World>()) {
#define X(T, ...) \
    if (!m_types->entities().contains(Proxy<T>::name())) Proxy<T>::m_typedefs(m_types.get());
    TALOS_XX_BUILTINS_LIST(X)
#undef X
}
