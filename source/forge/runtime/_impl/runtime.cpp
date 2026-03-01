/// Forge Modules
#include "forge/runtime/container.hpp"
#include "forge/runtime/service.hpp"

//  CONSTRUCTORS  //

Forge::Runtime::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Runtime::Service::Service(XI::Container* services) :
    m_services(services), m_async(m_services->get<Async::Service>()) {}
