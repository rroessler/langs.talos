/// Forge Modules
#include "forge/testing/service.hpp"
#include "forge/runtime/container.hpp"
#include "forge/testing/registry.hpp"

//  CONSTRUCTORS  //

Forge::Testing::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Testing::Service::Service(XI::Container* services) :
    m_services(services),
    m_async(m_services->get<Async::Service>()),
    m_session(m_services->get<Session>()),
    m_registry(m_services->get<Registry>()) {}
