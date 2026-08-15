#ifndef _TALOS_RELINT_OPTIONS_HPP
#define _TALOS_RELINT_OPTIONS_HPP

/// Talos Includes
#include "talos/forward/relint.hpp"

namespace Talos::Relint {

/// @brief Formatter Options.
struct Options { //  PROPERTIES  //

  /// @brief Enables all the recommended options.
  bool recommended = true;

  /// @brief The rules override severities to be enabled.
  $::Map::Dict<Severity> rules = {};

  /// @brief The available rules to be enabled.
  std::vector<$::String::Buffer> plugins = {};

  /// @brief Available rule overrides ignores reporters.
  $::Map::Base<Diagnostic::Code, Severity> overrides = {};

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding linting options.
   * @param value                     Value to decode.
   */
  static Options m_decode(const $::Serde::Value &value);
};

} // namespace Talos::Relint

#endif
