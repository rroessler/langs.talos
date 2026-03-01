#ifndef _XLSP_PROTOCOL_LOCATION_HPP
#define _XLSP_PROTOCOL_LOCATION_HPP

/// XLSP Modules
#include "xlsp/protocol/range.hpp"

namespace XLSP {

    /// @brief Location Structure.
    struct Location {
        //  PROPERTIES  //

        /// @brief Range of location.
        Range range;

        /// @brief Resource of location.
        $::URI::Buffer resource;

        //  CONSTRUCTORS  //

        /// @brief Constructs an anonymous location.
        constexpr Location() : Location($::URI::Anonymous().buffer()) {}

        /**
         * @brief Constructs a base location.
         * @param uri                   URI resource.
         * @param range                 Range to bind.
         */
        constexpr Location(const $::URI::Buffer& uri, const Range& range = {}) : range(range), resource(uri) {}

        //  OPERATOR METHODS  //

        /// @brief Equality operator for locations.
        constexpr auto operator==(const Location& other) const {
            return std::tie(range, resource) == std::tie(other.range, other.resource);
        }

        /// @brief Comparison operator for locations.
        constexpr auto operator<=>(const Location& other) const { return range <=> other.range; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles encoding locations.
         * @param self                      Location instance.
         */
        static $::Serde::Object m_encode(const Location& self) {
            return { { "uri", $::Reflect::encode(self.resource) }, { "range", $::Reflect::encode(self.range) } };
        }

        /**
         * @brief Handles decoding locations.
         * @param value                     JSON value to decode.
         */
        static Location m_decode(const $::Serde::Value& value) {
            return {
                $::Reflect::decode<$::URI::Buffer>(value.at("uri")),
                $::Reflect::decode<Range>(value.at("range")),
            };
        }
    };

}  // namespace XLSP

#endif
