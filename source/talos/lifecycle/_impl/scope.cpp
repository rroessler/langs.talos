/// Talos Includes
#include "talos/lifecycle/scope.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Lifecycle::Scope::Scope(Runtime::Isolate *isolate) : Scope($::Global::get<Runtime::Container>(), isolate) {}
Talos::Lifecycle::Scope::Scope(XI::Container *services, Runtime::Isolate *isolate) :
    m_lifecycle(*services), m_isolate(isolate) {
  m_lifecycle->preload(isolate); // bind now
}

Talos::Lifecycle::Scope::~Scope() { m_lifecycle->unload(m_isolate); }
