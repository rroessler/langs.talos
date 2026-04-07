/// Talos Modules
#include "talos/bundle/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Bundle::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Bundle::Service::Service(XI::Container* services) : m_services(services), m_async(*m_services) {}

//  PUBLIC METHODS  //

int32_t Talos::Bundle::Service::bundle(const Options& options) { return m_async->launch<Worker>(m_services, options); }
