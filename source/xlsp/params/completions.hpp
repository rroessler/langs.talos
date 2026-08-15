#ifndef _XLSP_PARAMS_COMPLETIONS_HPP
#define _XLSP_PARAMS_COMPLETIONS_HPP

/// XLSP Includes
#include "xlsp/message/request.hpp"
#include "xlsp/protocol/completion.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP::Request {

/// @brief Document Completions Request.
template <> struct Params<Channel::DOCUMENT_COMPLETIONS> : public Document::Cursor {
  constexpr Params(const Document::Cursor &cursor) : Cursor(cursor) {}
};

/// @brief Document Completions Result.
template <> struct Result<Channel::DOCUMENT_COMPLETIONS> {
  //  PROPERTIES  //

  /// @brief Completions to be returned.
  std::vector<Completion> completions = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs outgoing completions.
   * @param completions             Results to bind.
   */
  constexpr Result(const std::vector<Completion> &completions = {}) : completions(completions) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs the outgoing completions result.
   * @param self                    Result to encode.
   */
  static $::Serde::Value m_encode(const Result &self) { return $::Serde::Encode(self.completions); }
};

} // namespace XLSP::Request

#endif
