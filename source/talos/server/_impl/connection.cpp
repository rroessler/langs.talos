/// Talos Modules
#include "talos/server/connection.hpp"
#include "talos/runtime/options.hpp"

//  CONSTRUCTORS  //

Talos::Server::Connection::Connection(XI::Container* services, const Options* options) :
    Define(options), m_services(services), m_async(m_services->get<Async::Service>()) {
    // prepare the utilities and events to be used
    m_utilities = m_services->get<Utilities>();
    m_events = m_services->get<Events>(this, m_utilities.get());

    // prepare an initial binder to be used
    auto bind = binder();

    // get the underlying events cache now
    auto events = m_events.get();

    // and prepare the base lifecycle events to be handled
    bind.on_request(events, &Events::on_initialize);
    bind.on_request(events, &Events::on_shutdown);
}
