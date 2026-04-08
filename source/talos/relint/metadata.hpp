#ifndef _TALOS_RELINT_METADATA_HPP
#define _TALOS_RELINT_METADATA_HPP

/// Talos Modules
#include "talos/relint/scope.hpp"
#include "talos/syntax/comparator.hpp"

namespace Talos::Relint {

    /// @brief Document Symbols Alias.
    using Symbols = std::vector<XLSP::Symbol>;

    /// @brief Relint Environment Metadata.
    class Metadata {
        //  TYPEDEFS  //

        /// @brief Allow the linter internal access.
        friend struct Analyzer;

        //  PROPERTIES  //

        /// @brief The available document symbols.
        Symbols m_symbols = {};

        /// @brief The sorted list of mirrors.
        std::vector<const Syntax::Node*> m_sorted = {};

        /// @brief Prepare the base references scope.
        $::Ptr::Unique<Scope> m_references = $::New().unique<Scope>();

        /// @brief Mirrors that contain node reflection data.
        $::Map<const Syntax::Node*, $::Ptr::Unique<Mirror>> m_mirrors = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a linter-context.
        explicit Metadata() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the available document symbols.
        inline constexpr const Symbols& symbols() const noexcept { return m_symbols; }

        /// @brief Gets the core references scoping.
        inline constexpr const Scope* references() const noexcept { return m_references.get(); }

        /**
         * @brief Denotes if a mirror is bound.
         * @param origin                Origin node.
         */
        bool bound(const Syntax::Node* origin) const;

        /**
         * @brief Handles resolving syntax mirrors from a node.
         * @param origin                Origin node.
         */
        const Mirror* resolve(const Syntax::Node* origin) const;

        /**
         * @brief Handles resolving syntax mirrors from a node.
         * @param origin                Origin node.
         * @param parent                Parent node.
         */
        Mirror* resolve(const Syntax::Node* origin, const Syntax::Node* parent = nullptr);

        /**
         * @brief Handles searching for a node mirror.
         * @param position              Search position.
         * @param filter                Optional filter.
         */
        const Mirror* search(const XLSP::Position& position) const noexcept;
        const Mirror* search(const XLSP::Position& position, Filter&& filter) const noexcept;

        /// @brief Handles filtering metadata.
        template <std::derived_from<Syntax::Node> T>
        inline constexpr std::vector<const T*> filter() const noexcept {
            // prepare all the validly filtered items
            std::vector<const T*> filtered = {};

            // attempt filtering now
            for (const auto* node : m_sorted) {
                if (node->is<T>()) filtered.emplace_back(node->as<T>());
            }

            // return the resulting nodes now
            return filtered;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles constructing a mirror.
         * @param origin                Origin node.
         * @param parent                Parent node.
         */
        $::Ptr::Unique<Mirror> m_create(const Syntax::Node* origin, const Syntax::Node* parent) const noexcept;
    };

}  // namespace Talos::Relint

#endif
