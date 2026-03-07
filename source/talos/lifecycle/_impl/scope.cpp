/// Talos Modules
#include "talos/lifecycle/scope.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Lifecycle::Scope::Scope(Runtime::Isolate* isolate) : Scope($::Global::get<Runtime::Container>(), isolate) {}
Talos::Lifecycle::Scope::Scope(XI::Container* services, Runtime::Isolate* isolate) :
    m_lifecycle(services->get<Lifecycle::Service>()), m_isolate(isolate) {
    m_lifecycle->preload(isolate);
}

Talos::Lifecycle::Scope::~Scope() { m_lifecycle->unload(m_isolate); }
