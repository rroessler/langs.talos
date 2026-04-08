#ifndef _TALOS_SERVER_UTILITIES_HPP
#define _TALOS_SERVER_UTILITIES_HPP

/// Talos Modules
#include "talos/forward/server.hpp"
#include "talos/relint/mirror.hpp"

namespace Talos::Server {

    /// @brief Server Utilities Class.
    class Utilities : public XI::Define<Utilities, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Bound container of services.
        XI::Container* m_services;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs the underlying utilities.
        explicit Utilities();
        explicit Utilities(XI::Container* services);

        //  PUBLIC METHODS  //

        /**
         * @brief Normalizes a range from the client.
         * @param range                     Range to normalize.
         */
        XLSP::Range range_to_client(const XLSP::Range& range) const;
        XLSP::Range range_to_server(const XLSP::Range& range) const;

        /**
         * @brief Normalizes a position from the client.
         * @param position                  Position to normalize.
         */
        XLSP::Position position_to_client(const XLSP::Position& position) const;
        XLSP::Position position_to_server(const XLSP::Position& position) const;

        /**
         * @brief Converts syntax to a location.
         * @param node                      Node to be converted.
         */
        XLSP::Location syntax_to_client(const Syntax::Node* node) const;
        XLSP::Location syntax_to_client(const Relint::Mirror* mirror) const;

        /**
         * @brief Gets the syntax-metadata at a resource.
         * @param resource                  Resource value.
         */
        const Relint::Metadata* syntax_view_at(const $::URI::View& resource) const;

        /**
         * @brief Gets a syntax-node at a location.
         * @param resource                  Resource value.
         * @param position                  Position value.
         * @param filter                    Optional filter.
         */
        const Relint::Mirror* syntax_node_at(
            const $::URI::View& resource, const XLSP::Position& position, Relint::Filter&& filter = nullptr) const;

        /**
         * @brief Gets a syntax-node at a location.
         * @param resource                  Resource value.
         * @param position                  Position value.
         */
        template <std::derived_from<Syntax::Node>... Ts>
        inline constexpr const Relint::Mirror* syntax_node_at(
            const $::URI::View& resource, const XLSP::Position& position) const {
            return syntax_node_at(resource, position, [](const Syntax::Node* node) { return node->is<Ts...>(); });
        }

        /**
         * @brief Gets a variable definition node at a location.
         * @param resource                  Resource value.
         * @param position                  Position value.
         */
        const Relint::Mirror* vardef_node_at(const $::URI::View& resource, const XLSP::Position& position) const;

        /**
         * @brief Gets a type-definition node at a location.
         * @param resource                  Resource value.
         * @param position                  Position value.
         */
        const Relint::Mirror* typedef_node_at(const $::URI::View& resource, const XLSP::Position& position) const;

        /**
         * @brief Gets a definition node at a location.
         * @param resource                  Resource value.
         * @param position                  Position value.
         */
        const Relint::Mirror* anydef_node_at(const $::URI::View& resource, const XLSP::Position& position) const;
    };

}  // namespace Talos::Server

#endif
