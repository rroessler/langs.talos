#ifndef _FORGE_RELINT_METADATA_HPP
#define _FORGE_RELINT_METADATA_HPP

/// Forge Modules
#include "forge/relint/mirror.hpp"
#include "forge/syntax/comparator.hpp"

namespace Forge::Relint {

    /// @brief Relint Environment Metadata.
    class Metadata {
        //  TYPEDEFS  //

        /// @brief Allow the linter internal access.
        friend struct Analyzer;

        //  PROPERTIES  //

        /// @brief The sorted list of mirrors.
        std::vector<const Syntax::Node*> m_sorted = {};

        /// @brief Mirrors that contain node reflection data.
        $::Map<const Syntax::Node*, $::Ptr::Unique<Mirror>> m_mirrors = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a linter-context.
        explicit Metadata() = default;

        //  PUBLIC METHODS  //

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
         */
        const Mirror* search(const XLSP::Position& position) const noexcept;

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

}  // namespace Forge::Relint

#endif
