#ifndef _TALOS_SERVER_TRANSPORT_HPP
#define _TALOS_SERVER_TRANSPORT_HPP

/// Talos Includes
#include "talos/forward/server.hpp"

namespace Talos::Server {

    /// @brief Transport thread handler.
    class Transport : public XSIO::Task::Abstract<Transport> {
        //  PROPERTIES  //

        /// @brief Core transport instance.
        Connection* m_connection;

        /// @brief Core transport dispatcher.
        XLSP::Event::Dispatcher m_dispatcher;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a transport task.
         * @param connection                Server connection.
         */
        explicit Transport(Connection* connection);

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the transport thread.
        $_NORETURN void m_execute();
    };

}  // namespace Talos::Server

#endif
