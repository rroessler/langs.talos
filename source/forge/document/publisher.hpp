#ifndef _FORGE_DOCUMENT_PUBLISHER_HPP
#define _FORGE_DOCUMENT_PUBLISHER_HPP

/// Forge Modules
#include "forge/forward/document.hpp"
#include "forge/forward/module.hpp"
#include "forge/forward/server.hpp"

namespace Forge::Document {

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
         * @brief Forces an update event to occur.
         * @param resource                  Document resource.
         */
        void update(const $::URI::View& resource);

        /**
         * @brief Handles clearing document diagnostics.
         * @param resource                  Document resource.
         */
        void clear(const $::URI::View& resource);

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

}  // namespace Forge::Document

#endif
