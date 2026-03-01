#ifndef _FORGE_RESOURCE_LOCATION_HPP
#define _FORGE_RESOURCE_LOCATION_HPP

/// Forge Modules
#include "forge/forward/resource.hpp"

namespace Forge::Resource {

    /// @brief View-Only Location Structure.
    class Location : public $::Printable {
        //  PROPERTIES  //

        /// @brief Range of location.
        XLSP::Range m_range;

        /// @brief Resource of location.
        $::URI::View m_resource;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an anonymous location.
        constexpr Location() : Location($::URI::Anonymous()) {}

        /**
         * @brief Constructs a base location.
         * @param resource              URI resource.
         * @param range                 Range to bind.
         */
        constexpr Location(const $::URI::View& resource, const XLSP::Range& range = {}) :
            m_range(range), m_resource(resource) {}

        //  OPERATOR METHODS  //

        /// @brief Equality operator for locations.
        inline constexpr auto operator==(const Location& other) const {
            return std::tie(m_range, m_resource) == std::tie(other.m_range, other.m_resource);
        }

        /// @brief Comparison operator for locations.
        inline constexpr auto operator<=>(const Location& other) const { return m_range <=> other.m_range; }

        //  PUBLIC METHODS  //

        inline constexpr XLSP::Range& range() noexcept { return m_range; }
        inline constexpr const XLSP::Range& range() const noexcept { return m_range; }
        inline constexpr $::URI::View resource() const noexcept { return m_resource; }
        inline constexpr bool anonymous() const noexcept { return m_resource == $::URI::Anonymous(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles formatting locations.
         * @param os                    Output stream.
         * @param self                  Location instance.
         */
        static inline void m_print($::Stream::Output& os, const Location& self) {
            os << self.m_resource.relative() << ':' << self.m_range.start;
        }
    };

}  // namespace Forge::Resource

#endif
