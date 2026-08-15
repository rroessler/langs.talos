#ifndef _XLSP_PARAMS_DIAGNOSTICS_HPP
#define _XLSP_PARAMS_DIAGNOSTICS_HPP

/// XLSP Includes
#include "xlsp/message/notification.hpp"
#include "xlsp/protocol/diagnostic.hpp"
#include "xlsp/protocol/document.hpp"

namespace XLSP::Notification {

/// @brief Publish Diagnostics Parameters.
template <> struct Params<Channel::DIAGNOSTICS_PUBLISH> {
  //  PROPERTIES  //

  /// @brief The baseline document identifier.
  Document::Identifier identifier = {};

  /// @brief The associated array of diagnostics.
  std::vector<Diagnostic> diagnostics = {};

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs document open parameters.
   * @param resource                      Document resource.
   * @param diagnostics                   Diagnostics to bind.
   */
  explicit Params(const $::URI::Buffer &resource, const std::vector<Diagnostic> &diagnostics = {}) :
      identifier(resource), diagnostics(diagnostics) {}

  /**
   * @brief Constructs document open parameters.
   * @param identifier                    Document to bind.
   * @param diagnostics                   Diagnostics to bind.
   */
  explicit Params(const Document::Identifier &identifier, const std::vector<Diagnostic> &diagnostics = {}) :
      identifier(identifier), diagnostics(diagnostics) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Encodes the parameters.
   * @param self                          Diagnostics parameters.
   */
  static inline $::Serde::Value m_encode(const Params &self) {
    // ensure we cast the instance to a suitable output
    auto params = *$::Serde::Encode(self.identifier).as<$::Serde::Object>();
    params.emplace("diagnostics", $::Serde::Encode(self.diagnostics));
    return params; // and return the final diagnostics constructed
  }
};

} // namespace XLSP::Notification

#endif
