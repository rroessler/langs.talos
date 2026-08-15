#ifndef _XLSP_PROTOCOL_DIAGNOSTIC_HPP
#define _XLSP_PROTOCOL_DIAGNOSTIC_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"

namespace XLSP {

/// @brief Diagnostic Resource.
struct Diagnostic {
  //  TYPEDEFS  //

  /// @brief Semantic Diagnostic Code.
  using Code = int32_t;

  /// @brief Available diagnostic tags.
  enum class Tag : uint8_t { UNNECESSARY = 1, DEPRECATED = 2 };

  /// @brief Diagnostic Severities.
  enum class Severity : uint8_t { NONE = 0, ERROR = 1, WARN = 2, INFO = 3, HINT = 4 };

  //  PROPERTIES  //

  /// @brief Diagnostic tags.
  $::Enum::Flags<Tag> tags = {};

  /// @brief Current severity value.
  Severity severity = Severity::NONE;

  /// @brief Associated diagnostic code.
  Code code = -1;

  /// @brief Range of the diagnostic.
  Range range = {};

  /// @brief Human-readable source of the diagnostic.
  $::String::Buffer source = "";

  /// @brief Diagnostic message value.
  $::String::Buffer message = "";

  //  CONSTRUCTORS  //

  /// @brief Default constructor.
  explicit Diagnostic() = default;

  /**
   * @brief Constructs a diagnostic.
   * @param range                 Range to bind.
   * @param message               Diagnostic message.
   */
  explicit Diagnostic(const Range &range, const $::String::Buffer &message = "") : range(range), message(message) {}

  //  OPERATOR METHODS  //

  /// @brief Handles equality between diagnostics.
  inline constexpr auto operator==(const Diagnostic &other) const {
    return code == other.code && range == other.range && message == other.message;
  }

  /// @brief Handles comparison between diagnostics.
  inline constexpr auto operator<=>(const Diagnostic &other) const {
    return std::tie(code, range, message) <=> std::tie(other.code, other.range, other.message);
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding diagnostic values.
   * @param self                      Diagnostic to encode.
   */
  static inline $::Serde::Value m_encode(const Diagnostic &self) {
    // prepare the base diagnostic
    $::Serde::Object diagnostic = {
        {"code", self.code},
        {"message", self.message},
        {"range", $::Serde::Encode(self.range)},
    };

    // prepare a set of tags to be assigned to the diagnostics
    auto tags = $::Serde::Array();

    // push all the tags that we have found now
    if (self.tags.test(Tag::DEPRECATED)) tags.emplace_back(Tag::DEPRECATED);
    if (self.tags.test(Tag::UNNECESSARY)) tags.emplace_back(Tag::UNNECESSARY);

    // add all the optional items now to be used
    if (tags.size()) diagnostic["tags"] = tags;
    if (self.source.size()) diagnostic["source"] = self.source;
    if (self.severity != Severity::NONE) diagnostic["severity"] = static_cast<uint8_t>(self.severity);

    // return the resulting details
    return diagnostic;
  }
};

} // namespace XLSP

#endif
