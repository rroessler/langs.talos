/// Talos Includes
#include "talos/import/worker.hpp"
#include "talos/import/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/isolate.hpp"

//  CONSTRUCTORS  //

Talos::Import::Worker::Worker(Result *deferred, const $::URI::Buffer &resource) :
    Worker($::Global::get<Runtime::Container>(), deferred, resource) {}

Talos::Import::Worker::Worker(XI::Container *services, Result *deferred, const $::URI::Buffer &resource) :
    m_resource(resource), m_modules(*services), m_deferred(deferred) {}

//  PRIVATE METHODS  //

void Talos::Import::Worker::m_execute() { m_deferred->resolve(m_thread, m_modules->fetch(m_resource)); }
