/// Talos Modules
#include "talos/server/transport.hpp"
#include "talos/server/connection.hpp"

//  CONSTRUCTORS  //

Talos::Server::Transport::Transport(Connection* connection) : m_connection(connection), m_dispatcher(connection) {}

//  PRIVATE METHODS  //

$_NORETURN void Talos::Server::Transport::m_execute() {
    m_thread->shutdown(m_connection->transport()->listen(&m_dispatcher));
}
