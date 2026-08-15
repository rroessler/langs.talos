/// Talos Includes
#include "talos/document/service.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Document::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Document::Service::Service(XI::Container *services) : m_publisher(*services) {}
