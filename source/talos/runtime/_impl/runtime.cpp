/// Talos Modules
#include "talos/runtime/container.hpp"
#include "talos/runtime/service.hpp"

//  CONSTRUCTORS  //

Talos::Runtime::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Runtime::Service::Service(XI::Container* services) : m_services(services), m_async(*m_services) {}
