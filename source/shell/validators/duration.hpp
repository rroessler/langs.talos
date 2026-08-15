#ifndef _SHELL_VALIDATORS_DURATION_HPP
#define _SHELL_VALIDATORS_DURATION_HPP

/// Vendor Includes
#include <CLI/CLI.hpp>
#include <xtdlib/xtdlib.hpp>

namespace Shell::Validator {

/// @brief Helper Duration Validator.
struct Duration : public CLI::Validator {
  //  CONSTRUCTORS  //

  /// @brief Constructs a duration validator.
  explicit Duration() : Validator(m_transform, "TIME [UNIT]") {}

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles transforming durations.
   * @param input                     Input to transform.
   */
  static $::String::Buffer m_transform($::String::Buffer &input);
};

} // namespace Shell::Validator

#endif
