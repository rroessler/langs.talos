#ifndef _XLSP_EVENT_EMITTER_HPP
#define _XLSP_EVENT_EMITTER_HPP

/// XLSP Include
#include "xlsp/forward/event.hpp"
#include "xlsp/forward/server.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Event {

/// @brief Handles dispatching of incoming LSP messages.
class Emitter {
  //  PROPERTIES  //

  /// @brief Underlying cache instance.
  Server::Connection *m_connection;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an events emitter.
   * @param connection                Connection instance.
   */
  explicit Emitter(Server::Connection *connection) : m_connection(connection) {}

  //  PUBLIC METHODS  //

  /**
   * @brief Handles incoming notifications.
   * @param method                    Notification method.
   * @param params                    Notification parameters.
   */
  bool on_notify(const Message::Method &method, const Message::Params &params);

  /**
   * @brief Handles incoming requests.
   * @param id                        Request id.
   * @param method                    Request method.
   * @param params                    Request parameters.
   */
  bool on_request(const Request::Identifier &id, const Message::Method &method, const Message::Params &params);

  /**
   * @brief Handles incoming responses.
   * @param id                        Response id.
   * @param result                    Response result.
   */
  bool on_response(const Request::Identifier &id, const Message::Result<$::Serde::Value> &result);

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles cancelling requests.
   * @param params                    Cancel parameters.
   */
  void m_cancel(const Message::Params &params);
};

} // namespace XLSP::Event

#endif
