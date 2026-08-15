#ifndef _TALOS_SERVER_TRANSPORT_HPP
#define _TALOS_SERVER_TRANSPORT_HPP

/// Talos Includes
#include "talos/async/entry.hpp"
#include "talos/forward/server.hpp"

namespace Talos::Server {

/// @brief Transport thread handler.
class Transport : public Async::Entry {
  //  PROPERTIES  //

  /// @brief Core transport instance.
  Connection *m_connection;

  /// @brief Core transport dispatcher.
  XLSP::Event::Emitter m_emitter;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a transport task.
   * @param connection                Server connection.
   */
  explicit Transport();
  explicit Transport(Connection *connection);
  explicit Transport(XI::Container *services);

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles executing the transport thread.
  $_NORETURN void m_execute();
};

} // namespace Talos::Server

#endif
