/// XLSP Includes
#include "xlsp/event/emitter.hpp"
#include "xlsp/server/connection.hpp"

/// Forward Declarations
$_FWD(XLSP::Event, class Responder)

//  TYPEDEFS  //

class XLSP::Event::Responder {
  //  PROPERTIES  //

  /// @brief Starting time of response.
  $::Chrono::Point m_timestamp = $::Chrono::Point();

  /// @brief Incoming request method.
  $::String::Buffer m_method;

  /// @brief Connection instance to use.
  Server::Connection *m_connection;

  /// @brief Request identifier.
  Request::Identifier m_identifier;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a responder.
   * @param id                Request identifier.
   * @param method            Request method.
   * @param connection        Connection instance.
   */
  constexpr Responder(const Request::Identifier &id, const Message::Method &method, Server::Connection *connection) :
      m_method(method), m_connection(connection), m_identifier(id) {}

  //  OPERATOR METHODS  //

  /**
   * @brief Handles launching a response.
   * @param result                    Result to return.
   */
  inline void operator()(const Message::Result<$::Serde::Value> &result) const {
    // ensure the server is accesible for replying now
    $_ASSERT(m_connection, "Server reference missing");

    // check if a cancellation occured or the server is quitting
    if (m_cancelled(m_identifier) || m_connection->quitting()) return;

    // prepare the output duration to be shown
    auto duration = $::Chrono::Point() - m_timestamp;

    // show the outgoing reply details and the error if necessary
    $_TRACE("<-- reply: {0}({1}) {2}", m_method, m_identifier, duration);
    if (auto *error = std::get_if<Error>(&result)) $_ERROR("<-- {0}", *error);

    // declare as responded now
    m_respond(result);
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles actually responding.
   * @param result                    Result to return.
   */
  inline void m_respond(const Message::Result<$::Serde::Value> &result) const {
    m_connection->respond(m_identifier, result);
  }

  /**
   * @brief Checks for current cancellations and handles them.
   * @param id                            Identifier to query.

   */
  inline bool m_cancelled(const Request::Identifier &id) const {
    // get the incoming events instance now
    auto *events = m_connection->events();

    // check if not currently cancelled and ignore if it is
    $_UNUSED $_AUTO = $::Lock::guard(events->mutex.cancel);
    if (!events->cancellations.contains(id)) return false;

    // should be cancelled so remove the identifier from use
    events->cancellations.erase(id), $_TRACE("<-- reply cancelled: {0}({1})", m_method, id);

    // and attempt responding as necessary for cancelled requests
    return m_respond(Error(Error::Code::REQUEST_CANCELLED)), true;
  }
};

//  PUBLIC METHODS  //

bool XLSP::Event::Emitter::on_notify(const Message::Method &method, const Message::Params &params) {
  // denote any incoming events to be shown
  $_TRACE("--> notification: {0}", method);

  // check for incoming exit codes now
  const auto exiting = method == Notification::Channel::LIFECYCLE_EXIT;
  if (exiting || m_connection->quitting()) return exiting ? false : true;

  // we bypass with our own cancel routine now
  if (method == Notification::Channel::QUERY_CANCEL) return m_cancel(params), true;

  // attempt finding a suitable handler to be used
  const auto &notifications = m_connection->events()->notifications;
  auto handler = notifications.find(method); // get the notification now

  if (handler != notifications.cend()) handler->second(params); // attempt handling
  else if (!method.starts_with("$/")) $_WARN("Unhandled notification: {0}", method);

  // otherwise declare as valid now
  return true;
}

bool XLSP::Event::Emitter::on_request(
    const Request::Identifier &id, const Message::Method &method, const Message::Params &params
) {
  // attempt finding a suitable handler to be used
  auto reply = Responder(id, method, m_connection);

  // if we are quitting then ignore the instance
  if (m_connection->quitting()) return reply(Error(Error::Code::REQUEST_INVALID)), true;

  // denote any incoming events to be shown here
  $_TRACE("--> request: {0}({1})", method, id);

  // prepare the incoming requests available
  const auto &requests = m_connection->events()->requests;

  // handle as necessary now
  if (requests.contains(method)) return requests.at(method)(params, std::move(reply)), true;

  // declare as an error when not found (but still succeed the handler)
  auto message = fmt::format("Request '{0}' not found", method);
  return reply(Error(Error::Code::METHOD_MISSING, message)), true;
}

bool XLSP::Event::Emitter::on_response(const Request::Identifier &id, const Message::Result<$::Serde::Value> &result) {
  // get the queue of responders available
  auto *events = m_connection->events();
  auto &queue = events->responses;

  // prepare an initial response the be used
  Answer reply = [&id](const Message::Result<$::Serde::Value> &) { $_TRACE("Did not reply to: {0}", id); };

  // otherwise attempt matching a suitable request identifier now
  $_PP_SCOPE() {
    // ensure we lock other attempts to be made
    $_UNUSED $_AUTO = $::Lock::guard(events->mutex.reply);

    // attempt finding a corresponding callback now
    for (size_t ii = 0; ii < queue.size(); ++ii) {
      if (queue[ii].identifier != id) continue;
      reply = std::move(queue[ii].answer);
      queue.erase(queue.cbegin() + ii);
      break; // stop as found callback
    }
  }

  // if we were quitting then ignore the response
  if (m_connection->quitting()) return true;

  // and attempt calling the response as necessary now
  auto *error = std::get_if<Error>(&result);
  auto message = error ? fmt::format(" {0}", error->message()) : "";
  return $_TRACE("--> reply({0}){1}", id, message), reply(result), true;
}

//  PRIVATE METHODS  //

void XLSP::Event::Emitter::m_cancel(const Message::Params &params) {
  auto *events = m_connection->events(); // get the available
  auto cancellation = $::Serde::Decode<Request::Cancel>(params);

  // attempt updating our cancellations now
  $_UNUSED $_AUTO = $::Lock::guard(events->mutex.cancel);
  events->cancellations.emplace(cancellation.identifier);
}
