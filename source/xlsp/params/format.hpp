#ifndef _XLSP_PARAMS_FORMAT_HPP
#define _XLSP_PARAMS_FORMAT_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/format.hpp"

namespace XLSP::Request {

/// @brief Document Format Request.
template <> struct Params<Channel::DOCUMENT_FORMAT> : public Document::Layout {
  //  PROPERTIES  //

  /// @brief Bound formatter options.
  Format::Options options = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a formatting request.
   * @param identifier              Identifier to bind.
   * @param options                 Formatting options.
   */
  constexpr Params(const Document::Identifier &identifier, const Format::Options &options = {}) :
      Layout(identifier), options(options) {}

  /**
   * @brief Constructs a formatting request.
   * @param layout                  Document layout.
   * @param options                 Formatting options.
   */
  constexpr Params(const Document::Layout &layout, const Format::Options &options = {}) :
      Layout(layout), options(options) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the document parameters.
   * @param value                   Value to decode.
   */
  static Params m_decode(const $::Serde::Value &value) {
    auto options = $::Serde::Decode<Format::Options>(value.at("options"));
    return Params($::Serde::Decode<Layout>(value), options); // construct
  }
};

/// @brief Document Format Result.
template <> struct Result<Channel::DOCUMENT_FORMAT> {
  //  PROPERTIES  //

  /// @brief Outgoing edits for formatting.
  std::vector<Document::Edit> edits = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs formatting edits.
   * @param edits                   Document edits.
   */
  constexpr Result(const std::vector<Document::Edit> &edits = {}) : edits(edits) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the outgoing format result.
   * @param self                    Result to encode.
   */
  static $::Serde::Value m_encode(const Result &self) { return $::Serde::Encode(self.edits); }
};

} // namespace XLSP::Request

#endif
