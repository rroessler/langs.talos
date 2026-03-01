#ifndef _XLSP_EVENTS_RESPONDER_HPP
#define _XLSP_EVENTS_RESPONDER_HPP

/// XLSP Includes
#include "xlsp/forward/event.hpp"
#include "xlsp/forward/server.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Event {

    /// @brief Manages Event Responses.
    class Responder {
        //  PROPERTIES  //

        /// @brief Denotes if responded already.
        $::Atomic<bool> m_replied = false;

        /// @brief Starting time of response.
        $::Chrono::Point m_timestamp = $::Chrono::Point();

        $::String::Buffer m_method;        // Request method.
        Server::Connection* m_connection;  // Connection instance.
        Request::Identifier m_identifier;  // Request identifier.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a responder.
         * @param id                Request identifier.
         * @param method            Request method.
         * @param connection        Connection instance.
         */
        Responder(const Request::Identifier& id, const Message::Method& method, Server::Connection* connection) :
            m_method(method), m_connection(connection), m_identifier(id) {}

        /// @brief Copy constructor implementation.
        Responder(const Responder& other) :
            m_replied(other.m_replied.load()),
            m_timestamp(other.m_timestamp),
            m_method(other.m_method),
            m_connection(other.m_connection),
            m_identifier(other.m_identifier) {}

        //  OPERATOR METHODS  //

        /**
         * @brief Handles launching a response.
         * @param result                    Result to return.
         */
        void operator()(const Message::Result<$::Serde::Value>& result);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles actually responding.
         * @param result                    Result to return.
         */
        void m_respond(const Message::Result<$::Serde::Value>& result);

        /**
         * @brief Checks for current cancellations and handles them.
         * @param id                            Identifier to query.

         */
        bool m_cancelled(const Request::Identifier& id);
    };

}  // namespace XLSP::Event

#endif
