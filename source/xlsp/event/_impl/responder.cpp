/// XLSP Includes
#include "xlsp/event/responder.hpp"
#include "xlsp/server/connection.hpp"

//  OPERATOR METHODS  //

void XLSP::Event::Responder::operator()(const Message::Result<$::Serde::Value>& result) {
    $_ASSERT(m_connection, "Server reference missing");  // ensure the server is accesible
    $_EXPECT(!m_replied.exchange(true), "Replied twice to {0}({1})", m_method, m_identifier);

    // check if a cancellation occured or the server is quitting
    if (m_cancelled(m_identifier) || m_connection->quitting()) return;

    // prepare the output duration to be shown
    auto duration = $::Chrono::Point() - m_timestamp;

    $_TRACE("<-- reply: {0}({1}) {2}", m_method, m_identifier, duration);  // show now
    if (auto* error = std::get_if<Message::Error>(&result)) $_ERROR("<-- {0}", *error);

    // declare as responded now
    m_respond(result);
}

//  PRIVATE METHODS  //

void XLSP::Event::Responder::m_respond(const Message::Result<$::Serde::Value>& result) {
    m_connection->respond(m_identifier, result);
}

bool XLSP::Event::Responder::m_cancelled(const Request::Identifier& id) {
    // get the incoming events instance now
    auto* events = m_connection->events();

    // check if not currently cancelled and ignore if it is
    $_UNUSED $_AUTO = $::Lock::guard(events->mutex.cancel);
    if (!events->cancellations.contains(id)) return false;

    // should be cancelled so remove the identifier from use
    events->cancellations.erase(id), $_TRACE("<-- reply cancelled: {0}({1})", m_method, id);

    // and attempt responding as necessary for cancelled requests
    return m_respond(XLSP_ERROR(REQUEST_CANCELLED)), true;
}
