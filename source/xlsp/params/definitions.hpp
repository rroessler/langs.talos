#ifndef _XLSP_PARAMS_DEFINITIONS_HPP
#define _XLSP_PARAMS_DEFINITIONS_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP::Request {

/// @brief Document Variable Definitions Request.
template <> struct Params<Channel::DOCUMENT_VARDEF> : public Document::Cursor {
  constexpr Params(const Document::Cursor &cursor) : Cursor(cursor) {}
};

/// @brief Document Variable Definitions Result.
template <> struct Result<Channel::DOCUMENT_VARDEF> : public Document::Locations {
  constexpr Result(const Document::Locations &locations = {}) : Locations(locations) {}
};

/// @brief Document Type Definitions Request.
template <> struct Params<Channel::DOCUMENT_TYPEDEF> : public Document::Cursor {
  constexpr Params(const Document::Cursor &cursor) : Cursor(cursor) {}
};

/// @brief Document Type Definitions Result.
template <> struct Result<Channel::DOCUMENT_TYPEDEF> : public Document::Locations {
  constexpr Result(const Document::Locations &locations = {}) : Locations(locations) {}
};

/// @brief Document Declaration Request.
template <> struct Params<Channel::DOCUMENT_DECLARATION> : public Document::Cursor {
  constexpr Params(const Document::Cursor &cursor) : Cursor(cursor) {}
};

/// @brief Document Declaration Result.
template <> struct Result<Channel::DOCUMENT_DECLARATION> : public Document::Locations {
  constexpr Result(const Document::Locations &locations = {}) : Locations(locations) {}
};

/// @brief Document References Request.
template <> struct Params<Channel::DOCUMENT_REFERENCES> : public Document::Cursor {
  //  PROPERTIES  //

  /// @brief Include declaration reference.
  bool declaration = false;

  /**
   * @brief Constructs baseline parameters.
   * @param cursor                  Cursor instance.
   * @param declaration             Declaration flag.
   */
  constexpr Params(const Document::Cursor &cursor, bool declaration = false) :
      Cursor(cursor), declaration(declaration) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the document parameters.
   * @param value                         Value to decode.
   */
  static Params m_decode(const $::Serde::Value &value) {
    auto declaration = value.at("context").at("includeDeclaration");
    return Params($::Serde::Decode<Cursor>(value), !!declaration);
  }
};

/// @brief Document References Result.
template <> struct Result<Channel::DOCUMENT_REFERENCES> : public Document::Locations {
  constexpr Result(const Document::Locations &locations = {}) : Locations(locations) {}
};

} // namespace XLSP::Request

#endif
