#ifndef _XLSP_PARAMS_SYMBOLS_HPP
#define _XLSP_PARAMS_SYMBOLS_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/document.hpp"
#include "xlsp/protocol/symbol.hpp"

namespace XLSP::Request {

/// @brief Document Symbols Request.
template <> struct Params<Channel::DOCUMENT_SYMBOLS> : public Document::Layout {
  constexpr Params(const Document::Layout &layout) : Layout(layout) {}
};

/// @brief Document Symbols Result.
template <> struct Result<Channel::DOCUMENT_SYMBOLS> {
  //  PROPERTIES  //

  /// @brief All available workspace symbols.
  std::vector<Symbol> symbols = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs symbols results.
   * @param symbols                     Output symbols.
   */
  constexpr Result(const std::vector<Symbol> &symbols = {}) : symbols(symbols) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the outgoing symbols result.
   * @param self                    Result to encode.
   */
  static $::Serde::Value m_encode(const Result &self) { return $::Serde::Encode(self.symbols); }
};

} // namespace XLSP::Request

#endif
