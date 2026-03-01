/// XLSP Modules
#include "xlsp/event/dispatcher.hpp"
#include "xlsp/event/responder.hpp"
#include "xlsp/message/special.hpp"
#include "xlsp/server/connection.hpp"

//  PUBLIC METHODS  //

bool XLSP::Event::Dispatcher::on_notify(const Message::Method& method, const Message::Params& params) {
    // denote any incoming events to be shown
    $_TRACE("--> notification: {0}", method);

    // check for incoming exit codes now
    const auto exiting = method == XLSP_MESSAGE_CHANNEL(LIFECYCLE_EXIT);
    if (exiting || m_connection->quitting()) return exiting ? false : true;

    // we bypass with our own cancel routine now
    if (method == XLSP_MESSAGE_CHANNEL($_CANCEL)) return m_cancel(params), true;

    // attempt finding a suitable handler to be used
    auto& notifications = m_connection->events()->notifications;
    auto handler = notifications.find(method);  // get the notification now

    if (handler != notifications.cend()) handler->second(params);  // attempt handling
    else if (!method.starts_with("$/")) $_WARN("Unhandled notification: {0}", method);

    // otherwise declare as valid now
    return true;
}

bool XLSP::Event::Dispatcher::on_request(
    const Request::Identifier& id, const Message::Method& method, const Message::Params& params) {
    // attempt finding a suitable handler to be used
    auto reply = Responder(id, method, m_connection);

    // if we are quitting then ignore the instance
    if (m_connection->quitting()) return reply(XLSP_ERROR(INVALID_REQUEST)), true;

    // denote any incoming events to be shown here
    $_TRACE("--> request: {0}({1})", method, id);

    // prepare the incoming requests available
    const auto& requests = m_connection->events()->requests;

    // handle as necessary now
    if (requests.contains(method)) return requests.at(method)(params, std::move(reply)), true;

    // declare as an error when not found (but still succeed the handler)
    return reply(XLSP_ERROR(METHOD_MISSING, fmt::format("Request '{0}' not found", method))), true;
}

bool XLSP::Event::Dispatcher::on_response(
    const Request::Identifier& id, const Message::Result<$::Serde::Value>& result) {
    // get the queue of responders available
    auto* events = m_connection->events();
    auto& queue = events->responses;

    // prepare an initial response the be used
    Answer reply = [&id](const Message::Result<$::Serde::Value>&) { $_TRACE("Did not reply to: {0}", id); };

    // otherwise attempt matching a suitable request identifier now
    $_PP_SCOPE() {
        // ensure we lock other attempts to be made
        $_UNUSED $_AUTO = $::Lock::guard(events->mutex.reply);

        // attempt finding a corresponding callback now
        for (size_t ii = 0; ii < queue.size(); ++ii) {
            if (queue[ii].identifier != id) continue;
            reply = std::move(queue[ii].answer);
            queue.erase(queue.cbegin() + ii);
            break;  // stop as found callback
        }
    }

    // if we were quitting then ignore the response
    if (m_connection->quitting()) return true;

    // and attempt calling the response as necessary now
    auto* error = std::get_if<Message::Error>(&result);
    auto message = error ? fmt::format(" {0}", error->message()) : "";
    return $_TRACE("--> reply({0}){1}", id, message), reply(result), true;
}

//  PRIVATE METHODS  //

void XLSP::Event::Dispatcher::m_cancel(const Message::Params& params) {
    auto* events = m_connection->events();  // get the available events
    auto cancellation = $::Reflect::decode<XLSP_NOTIFICATION($_CANCEL)>(params);

    // attempt updating our cancellations now
    $_UNUSED $_AUTO = $::Lock::guard(events->mutex.cancel);
    events->cancellations.emplace(cancellation.identifier);
}
