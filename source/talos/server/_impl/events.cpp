/// Talos Includes
#include "talos/server/events.hpp"
#include "talos/document/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/server/connection.hpp"

//  CONSTRUCTORS  //

Talos::Server::Events::Events() : Events($::Global::get<Runtime::Container>()) {}
Talos::Server::Events::Events(XI::Container *services) : Events(services, *services) {}
Talos::Server::Events::Events(XI::Container *services, Connection *connection) :
    m_connection(connection), m_utilities(m_connection->utilities()), m_documents(*services) {}
