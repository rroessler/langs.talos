/// Forge Modules
#include "forge/lifecycle/scope.hpp"
#include "forge/lifecycle/service.hpp"
#include "forge/runtime/container.hpp"

//  CONSTRUCTORS  //

Forge::Lifecycle::Scope::Scope(Runtime::Isolate* isolate) : Scope($::Global::get<Runtime::Container>(), isolate) {}
Forge::Lifecycle::Scope::Scope(XI::Container* services, Runtime::Isolate* isolate) :
    m_lifecycle(services->get<Lifecycle::Service>()), m_isolate(isolate) {
    m_lifecycle->preload(isolate);
}

Forge::Lifecycle::Scope::~Scope() { m_lifecycle->unload(m_isolate); }
