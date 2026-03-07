/// Talos Modules
#include "talos/testing/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/testing/registry.hpp"

//  CONSTRUCTORS  //

Talos::Testing::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Testing::Service::Service(XI::Container* services) :
    m_services(services),
    m_async(m_services->get<Async::Service>()),
    m_session(m_services->get<Session>()),
    m_registry(m_services->get<Registry>()) {}
