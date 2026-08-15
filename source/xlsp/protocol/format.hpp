#ifndef _XLSP_PROTOCOL_FORMAT_HPP
#define _XLSP_PROTOCOL_FORMAT_HPP

/// XLSP Include
#include "xlsp/forward/protocol.hpp"

namespace XLSP::Format {

/// @brief Formatting Options.
struct Options {
  //  PROPERTIES  //

  size_t indent_width = 4;   // Spaces indentation width.
  bool indent_spaces = true; // Indent with spaces.

  bool newline_final = true;     // Insert a final newline.
  bool newline_trailing = false; // Trim trailing newlines.

  /// @brief Trim any trailing whitespace on lines.
  bool whitespace_trailing = false;

  /// @brief Additional formatting properties.
  $::Serde::Object custom_properties = {};

  //  CONSTRUCTORS  //

  /// @brief Default constructor.
  constexpr Options() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding a formatting options.
   * @param value                     Value to decode.
   */
  static Options m_decode(const $::Serde::Value &value) {
    // prepare the base change
    auto options = Options();

    // get the required options
    options.indent_width = value.at<size_t>("tabSize", 4);
    options.indent_spaces = *value.at<$::Serde::Boolean>("insertSpaces");

    // and the optional items now
    if (auto *flag = value.at<$::Serde::Boolean>("insertFinalNewline")) options.newline_final = *flag;
    if (auto *flag = value.at<$::Serde::Boolean>("trimFinalNewlines")) options.newline_trailing = *flag;
    if (auto *flag = value.at<$::Serde::Boolean>("trimTrailingWhitespace")) options.whitespace_trailing = *flag;

    // and construct the additional properties view
    options.custom_properties = *value.as<$::Serde::Object>();

    // and return the resulting options
    return options;
  }
};

} // namespace XLSP::Format

#endif
