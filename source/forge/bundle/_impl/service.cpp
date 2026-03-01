/// Forge Modules
#include "forge/bundle/service.hpp"
#include "forge/runtime/container.hpp"

//  CONSTRUCTORS  //

Forge::Bundle::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Forge::Bundle::Service::Service(XI::Container* services) :
    m_services(services), m_async(m_services->get<Async::Service>()) {}

//  PUBLIC METHODS  //

int32_t Forge::Bundle::Service::bundle(const Options& options) { return m_async->launch<Worker>(m_services, options); }
