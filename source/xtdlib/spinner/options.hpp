#ifndef _XTDLIB_SPINNER_OPTIONS_HPP
#define _XTDLIB_SPINNER_OPTIONS_HPP

/// Library Includes
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/spinner/frames.hpp"
#include "xtdlib/spinner/mode.hpp"

namespace $::Spinner {

/// @brief Spinner Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Denotes the spinner mode.
  Mode mode = Mode::RESOLVE;

  /// @brief The starting prefix value.
  String::Buffer prefix = "";

  /// @brief The starting suffix value.
  String::Buffer suffix = "";

  /// @brief The duration between refreshes.
  Chrono::Duration tick = 80ms;

  /// @brief Where to output the spinner.
  std::ostream &output = std::cout;

  /// @brief The current animation frames.
  Frames frames = Animation::dots();
};

} // namespace $::Spinner

#endif
