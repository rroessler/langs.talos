/// Talos Modules
#include "talos/server/connection.hpp"
#include "talos/runtime/options.hpp"

//  CONSTRUCTORS  //

Talos::Server::Connection::Connection(XI::Container* services, const Options* options) :
    Define(options), m_services(services), m_async(*m_services), m_documents(*m_services), m_utilities(*m_services) {
    // prepare the events seperately since it requires different items
    auto events = (m_events = m_services->get<Events>(this, m_utilities.get())).get();

    // prepare an initial binder to be used
    auto bind = binder();

    // and prepare the base lifecycle events to be handled
    bind.on_request(events, &Events::on_initialize);
    bind.on_request(events, &Events::on_shutdown);
}
