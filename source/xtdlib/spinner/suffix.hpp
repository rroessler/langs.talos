#ifndef _XTBLIB_SPINNER_SUFFIX_HPP
#define _XTDLIB_SPINNER_SUFFIX_HPP

/// Library Includes
#include "xtdlib/color/ansi.hpp"

namespace $::Spinner {

/// @brief Factory for generating suffixes.
static inline constexpr auto Suffix(const String::View &title) {
  return [title](const $::String::View &message) {
    auto prefix = fmt::to_string($::Dye::green(title));
    return prefix + ": " + fmt::to_string($::Dye::dim(message));
  };
}

} // namespace $::Spinner

#endif
