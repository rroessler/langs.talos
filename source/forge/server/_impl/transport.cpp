/// Forge Modules
#include "forge/server/transport.hpp"
#include "forge/server/connection.hpp"

//  CONSTRUCTORS  //

Forge::Server::Transport::Transport(Connection* connection) : m_connection(connection), m_dispatcher(connection) {}

//  PRIVATE METHODS  //

$_NORETURN void Forge::Server::Transport::m_execute() {
    m_thread->shutdown(m_connection->transport()->listen(&m_dispatcher));
}
