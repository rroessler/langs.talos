#ifndef _XLSP_PARAMS_LINKS_HPP
#define _XLSP_PARAMS_LINKS_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/anchor.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP::Request {

/// @brief Document Links Request.
template <> struct Params<Channel::DOCUMENT_LINKS> : public Document::Layout {
  constexpr Params(const Document::Layout &layout) : Layout(layout) {}
};

/// @brief Document Links Result.
template <> struct Result<Channel::DOCUMENT_LINKS> {
  //  PROPERTIES  //

  /// @brief All available workspace links.
  std::vector<Anchor> links = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs links results.
   * @param links                     Output links.
   */
  constexpr Result(const std::vector<Anchor> &links = {}) : links(links) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the outgoing links result.
   * @param self                    Result to encode.
   */
  static $::Serde::Value m_encode(const Result &self) { return $::Serde::Encode(self.links); }
};

} // namespace XLSP::Request

#endif
