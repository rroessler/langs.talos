#ifndef _XLSP_PROTOCOL_MARKUP_HPP
#define _XLSP_PROTOCOL_MARKUP_HPP

/// XLSP Include
#include "xlsp/forward/protocol.hpp"

namespace XLSP::Markup {

/// @brief Markup Content Container.
class Content {
  //  PROPERTIES  //

  /// @brief The attached markup kind.
  $::String::Buffer m_kind = "plaintext";

  /// @brief Streamed content value.
  std::stringstream m_os = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construction.
  constexpr Content() = default;

  /// @brief Allow assigning a desired kind.
  constexpr Content(const $::String::Buffer &kind) : m_kind(kind) {}

  //  PUBLIC METHODS  //

  /// @brief Denotes if the string-stream is empty.
  inline constexpr bool empty() const noexcept { return m_os.view().empty(); }

  /// @brief The associated markup kind.
  inline constexpr $::String::View kind() const noexcept { return m_kind; }

  /// @brief Gets the underlying stream value.
  inline constexpr std::ostream &stream() noexcept { return m_os; }

  /// @brief Gets a view of the markup stream buffer.
  inline constexpr $::String::Buffer buffer() const noexcept { return m_os.str(); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding markup content.
   * @param self                      Content to encode.
   */
  static $::Serde::Object m_encode(const Content &self) { return {{"kind", self.kind()}, {"value", self.buffer()}}; }
};

//  PUBLIC METHODS  //

/// @brief Factory for constructing "markdown" based content.
inline constexpr Content Formatted() { return Content("markdown"); }

/**
 * @brief Constructs a code-block.
 * @param content               Code content.
 * @param language              Optional language.
 */
inline constexpr std::vector<$::String::Buffer>
Code(const $::String::Buffer &content, const $::String::Buffer &language = "") {
  return {"```" + language, content, "```"};
}

} // namespace XLSP::Markup

#endif
