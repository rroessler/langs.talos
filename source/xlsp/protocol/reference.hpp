#ifndef _XLSP_PROTOCOL_REFERENCE_HPP
#define _XLSP_PROTOCOL_REFERENCE_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"

namespace XLSP {

/// @brief Reference Structure.
struct Reference {
  //  PROPERTIES  //

  /// @brief Range of reference.
  Range range = {};

  /// @brief Resource of reference.
  $::URI::Buffer resource = {};

  //  CONSTRUCTORS  //

  /// @brief Constructs an anonymous reference.
  constexpr Reference() = default;

  /**
   * @brief Constructs a base reference.
   * @param uri                   URI resource.
   * @param range                 Range to bind.
   */
  constexpr Reference(const $::URI::Buffer &uri, const Range &range = {}) : range(range), resource(uri) {}

  //  OPERATOR METHODS  //

  /// @brief Equality operator for references.
  constexpr auto operator==(const Reference &other) const {
    return std::tie(range, resource) == std::tie(other.range, other.resource);
  }

  /// @brief Comparison operator for references.
  constexpr auto operator<=>(const Reference &other) const { return range <=> other.range; }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding references.
   * @param self                      Reference instance.
   */
  static $::Serde::Object m_encode(const Reference &self) {
    return {{"uri", $::Serde::Encode(self.resource)}, {"range", $::Serde::Encode(self.range)}};
  }

  /**
   * @brief Handles decoding references.
   * @param value                     JSON value to decode.
   */
  static Reference m_decode(const $::Serde::Value &value) {
    return {$::Serde::Decode<$::URI::Buffer>(value.at("uri")), $::Serde::Decode<Range>(value.at("range"))};
  }
};

} // namespace XLSP

#endif
