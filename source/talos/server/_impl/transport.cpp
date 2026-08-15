/// Talos Includes
#include "talos/server/transport.hpp"
#include "talos/runtime/container.hpp"
#include "talos/server/connection.hpp"

//  CONSTRUCTORS  //

Talos::Server::Transport::Transport() : Transport($::Global::get<Runtime::Container>()) {}
Talos::Server::Transport::Transport(XI::Container *services) : Transport(*services) {}
Talos::Server::Transport::Transport(Connection *connection) : m_connection(connection), m_emitter(connection) {}

//  PRIVATE METHODS  //

$_NORETURN void Talos::Server::Transport::m_execute() {
  m_thread->shutdown(m_connection->transport()->listen(&m_emitter));
}
