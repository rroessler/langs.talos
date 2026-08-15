#ifndef _XLSP_PARAMS_HOVER_HPP
#define _XLSP_PARAMS_HOVER_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/markup.hpp"

namespace XLSP::Request {

/// @brief Document Hover Request.
template <> struct Params<Channel::DOCUMENT_HOVER> : public Document::Cursor {
  constexpr Params(const Document::Cursor &cursor) : Cursor(cursor) {}
};

/// @brief Document Hover Result.
template <> struct Result<Channel::DOCUMENT_HOVER> {
  //  PROPERTIES  //

  /// @brief The outgoing hover contents.
  Markup::Content contents = {};

  /// @brief Highlighting range to bind.
  std::optional<Range> range = std::nullopt;

  //  CONSTRUCTORS  //

  /// @brief Constructs baseline hover contents.
  constexpr Result() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the outgoing hover result.
   * @param self                    Result to encode.
   */
  static $::Serde::Value m_encode(const Result &self) {
    if (self.contents.empty()) return $::Serde::Null();
    $::Serde::Object hover = {{"contents", $::Serde::Encode(self.contents)}};
    if (self.range.has_value()) hover["range"] = $::Serde::Encode(*self.range);
    return hover; // and return the resulting hover instance as necessary
  }
};

} // namespace XLSP::Request

#endif
