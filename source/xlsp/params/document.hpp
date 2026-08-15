#ifndef _XLSP_PARAMS_DOCUMENT_HPP
#define _XLSP_PARAMS_DOCUMENT_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP::Notification {

/// @brief Document Opened Notification.
template <> struct Params<Channel::DOCUMENT_OPENED> {
  //  PROPERTIES  //

  /// @brief The bound document value.
  Document document = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs document open parameters.
   * @param document                      Document to bind.
   */
  explicit Params(const Document &document = {}) : document(document) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the initialize request parameters.
   * @param json                          JSON to request.
   */
  static Params m_decode(const $::Serde::Value &value) {
    return Params($::Serde::Decode<Document>(value.at("textDocument")));
  }
};

/// @brief Document Closed Notification.
template <> struct Params<Channel::DOCUMENT_CLOSED> : public Document::Layout {
  constexpr Params(const Document::Layout &layout) : Layout(layout) {}
};

/// @brief Document Changed Notification.
template <> struct Params<Channel::DOCUMENT_CHANGED> : public Document::Layout {
  //  PROPERTIES  //

  /// @brief Document modifications.
  std::vector<Document::Change> changes = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a document changed instance.
   * @param identifier                    Document to bind.
   * @param changes                       Changes to bind.
   */
  explicit Params(const std::vector<Document::Change> &changes = {}) : changes(changes) {}
  explicit Params(const Document::Identifier &identifier, const std::vector<Document::Change> &changes = {}) :
      Layout(identifier), changes(changes) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the document parameters.
   * @param value                         Value to decode.
   */
  static Params m_decode(const $::Serde::Value &value) {
    auto identifier = $::Serde::Decode<Document::Identifier>(value.at("textDocument"));
    auto changes = $::Serde::Decode<Document::Change>(value.at("contentChanges", $::Serde::Array()));
    return Params(identifier, changes); // and construct the resulting parameters now
  }
};

} // namespace XLSP::Notification

#endif
