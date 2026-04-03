#ifndef _TALOS_SERVER_EVENTS_HPP
#define _TALOS_SERVER_EVENTS_HPP

/// Talos Includes
#include "talos/server/utilities.hpp"

namespace Talos::Server {

    /// @brief Lifecycle Handlers.
    class Events : public XI::Define<Events, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Available helper utilities.
        Utilities* m_utilities;

        /// @brief Attached connection instance.
        Connection* m_connection;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a connection instance.
         * @param utilities             Helper utilities.
         * @param connection            Server connection.
         */
        explicit Events(Connection* connection, Utilities* utilities) :
            m_utilities(utilities), m_connection(connection) {}

        //  PUBLIC METHODS  //

        void on_initialize(XLSP_REQUEST(LIFECYCLE_INITIALIZE) request);
        void on_shutdown(XLSP_REQUEST(LIFECYCLE_SHUTDOWN, XLSP::Event::Answer) request);

        void on_document_opened(const XLSP_NOTIFICATION(DOCUMENT_OPENED) & params);
        void on_document_closed(const XLSP_NOTIFICATION(DOCUMENT_CLOSED) & params);
        void on_document_changed(const XLSP_NOTIFICATION(DOCUMENT_CHANGED) & params);

        void on_workspace_watcher(const XLSP_NOTIFICATION(WORKSPACE_FILE_CHANGED) & params);

        void on_document_hover(XLSP_REQUEST(DOCUMENT_HOVER) request);
        void on_document_links(XLSP_REQUEST(DOCUMENT_LINKS) request);
        void on_document_format(XLSP_REQUEST(DOCUMENT_FORMAT) request);
        void on_document_symbols(XLSP_REQUEST(DOCUMENT_SYMBOLS) request);
        void on_document_completes(XLSP_REQUEST(DOCUMENT_COMPLETIONS) request);
        void on_document_typedef(XLSP_REQUEST(DOCUMENT_TYPE_DEFINITION) request);
        void on_document_vardef(XLSP_REQUEST(DOCUMENT_VARIABLE_DEFINITION) request);

       private:
        //  PRIVATE METHODS  //

        /// @brief Allows ignoring incoming notifications.
        template <XLSP::Message::Type M>
        void m_ignore(const XLSP::Notification::Params<M>&) {}

        /// @brief Allows ignoring incoming requests.
        template <XLSP::Message::Type M, bool Cancel = true>
        void m_ignore(XLSP::Request::Handle<M, XLSP::Event::Answer> handle) {
            if constexpr (!Cancel) handle.reply($::Serde::Null());
            else handle.reply(XLSP_ERROR(SERVER_CANCELLED));
        }
    };

}  // namespace Talos::Server

#endif
