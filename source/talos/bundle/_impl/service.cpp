/// Talos Includes
#include "talos/bundle/service.hpp"
#include "talos/async/service.hpp"
#include "talos/bundle/worker.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Bundle::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Bundle::Service::Service(XI::Container *services) : m_services(services) {}

//  PUBLIC METHODS  //

int32_t Talos::Bundle::Service::bundle(const Options &options) {
  Async::Service *async = *m_services; // prepare
  return async->launch<Worker>(m_services, options);
}
