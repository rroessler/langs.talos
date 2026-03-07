#ifndef _TALOS_SYNTAX_BOUNDS_HPP
#define _TALOS_SYNTAX_BOUNDS_HPP

/// Talos Modules
#include "talos/forward/syntax.hpp"
#include "talos/resource/location.hpp"

namespace Talos::Syntax {

    /// @brief Encapsulates Node Bounds.
    class Bounds : public Resource::Location {
        //  PROPERTIES  //

        /// @brief Encapsulates the outermost bounds.
        XLSP::Range m_bounds = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an anonymous location.
        constexpr Bounds() = default;

        /**
         * @brief Constructs a base location.
         * @param other                 Original location.
         */
        constexpr Bounds(const Resource::Location& other) : Bounds(other.resource(), other.range()) {}

        /**
         * @brief Constructs a base location.
         * @param resource              URI resource.
         * @param range                 Range to bind.
         */
        constexpr Bounds(const $::URI::View& resource, const XLSP::Range& range = {}) :
            Location(resource, range), m_bounds(range) {}

        /**
         * @brief Constructs a base location.
         * @param resource              URI resource.
         * @param range                 Range to bind.
         * @param bounds                Bounds to bind.
         */
        constexpr Bounds(const $::URI::View& resource, const XLSP::Range& range, const XLSP::Range& bounds) :
            Location(resource, range), m_bounds(bounds) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying bounds encapsulate.
        inline constexpr const XLSP::Range& bounds() const noexcept { return m_bounds; }
    };

}  // namespace Talos::Syntax

#endif
