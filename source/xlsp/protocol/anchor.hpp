#ifndef _XLSP_PROTOCOL_ANCHOR_HPP
#define _XLSP_PROTOCOL_ANCHOR_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"

namespace XLSP {

/// @brief Document Link (eg: Internal/External Website).
struct Anchor {
  //  PROPERTIES  //

  /// @brief Document Link Range.
  Range range = {};

  /// @brief The resource target to link.
  $::URI::Buffer target;

  /// @brief Link text to show on hover.
  $::String::Buffer tooltip = "";

  //  CONSTRUCTORS  //

  /// @brief Do not allow default construction.
  constexpr Anchor() = delete;

  /**
   * @brief Constructs an empty document.
   * @param resource                  Document resource.
   * @param range                     Range to bind.
   */
  constexpr Anchor(const $::URI::Buffer &resource, const Range &range = {}) : range(range), target(resource) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding a document link.
   * @param self                      Link to encode.
   */
  static $::Serde::Value m_encode(const Anchor &self) {
    // construct the basis of our link
    $::Serde::Object link = {
        {"range", $::Serde::Encode(self.range)},
        {"target", $::Serde::Encode(self.target)},
    };

    // bind the resulting tooltip if it has a size
    if (self.tooltip.size()) link["tooltip"] = self.tooltip;

    // return the reslting link
    return link;
  }
};

} // namespace XLSP

#endif
