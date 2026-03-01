/// Forge Modules
#include "forge/builtins/service.hpp"
#include "forge/runtime/container.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Forge::Builtins::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Builtins::Service::Service(XI::Container* services) :
    m_globals(services->when<Globals::Service>()), m_types($::New().unique<Type::World>()) {
#define X(T, ...) \
    if (!m_types->entities().contains(Proxy<T>::name())) Proxy<T>::m_typedefs(m_types.get());
    FORGE_XX_BUILTINS_LIST(X)
#undef X
}
