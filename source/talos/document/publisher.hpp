#ifndef _TALOS_DOCUMENT_PUBLISHER_HPP
#define _TALOS_DOCUMENT_PUBLISHER_HPP

/// Talos Modules
#include "talos/forward/document.hpp"
#include "talos/forward/module.hpp"
#include "talos/forward/server.hpp"

namespace Talos::Document {

    /// @brief Document Publisher Service.
    class Publisher : public XI::Define<Publisher, XI::Unique> {
        //  PROPERTIES  //

        /// @brief The underlying services container.
        XI::Container* m_services = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit Publisher() = default;

        /**
         * @brief Constructs a publisher instance.
         * @param services                  Services container.
         */
        explicit Publisher(XI::Container* services) : m_services(services) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Handles clearing document diagnostics.
         * @param resource                  Document resource.
         */
        void clear(const $::URI::View& resource);

        /**
         * @brief Forces an update event to occur.
         * @param resource                  Document resource.
         */
        void refresh(const $::URI::View& resource);
        void refresh(const std::vector<$::URI::View>& resources);
        void refresh(const std::vector<$::URI::Buffer>& resources);

        /**
         * @brief Handles publishing document diagnostics.
         * @param resource                  Document resource.
         * @param diagnostics               Diagnostics to publish.
         */
        void publish(const $::URI::View& resource, const std::vector<XLSP::Diagnostic>& diagnostics);

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the drafts instance.
        Import::Drafts* m_drafts();

        /// @brief Gets the underlying server connection.
        Server::Connection* m_connection();
    };

}  // namespace Talos::Document

#endif
