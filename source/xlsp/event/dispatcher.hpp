#ifndef _XLSP_EVENTS_DISPATCHER_HPP
#define _XLSP_EVENTS_DISPATCHER_HPP

/// XLSP Modules
#include "xlsp/forward/event.hpp"
#include "xlsp/forward/server.hpp"
#include "xlsp/message/request.hpp"

namespace XLSP::Event {

    /// @brief Handles dispatching of incoming LSP messages.
    class Dispatcher {
        //  PROPERTIES  //

        /// @brief Underlying cache instance.
        Server::Connection* m_connection;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an events dispatcher.
         * @param connection                Connection instance.
         */
        explicit Dispatcher(Server::Connection* connection) : m_connection(connection) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Handles incoming notifications.
         * @param method                    Notification method.
         * @param params                    Notification parameters.
         */
        bool on_notify(const Message::Method& method, const Message::Params& params);

        /**
         * @brief Handles incoming requests.
         * @param id                        Request id.
         * @param method                    Request method.
         * @param params                    Request parameters.
         */
        bool on_request(const Request::Identifier& id, const Message::Method& method, const Message::Params& params);

        /**
         * @brief Handles incoming responses.
         * @param id                        Response id.
         * @param result                    Response result.
         */
        bool on_response(const Request::Identifier& id, const Message::Result<$::Serde::Value>& result);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles cancelling requests.
         * @param params                    Cancel parameters.
         */
        void m_cancel(const Message::Params& params);
    };

}  // namespace XLSP::Event

#endif
