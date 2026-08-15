#ifndef _TALOS_LOCALE_OPTIONS_HPP
#define _TALOS_LOCALE_OPTIONS_HPP

/// Talos Includes
#include "talos/forward/locale.hpp"

namespace Talos::Locale {

/// @brief Locale Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Denotes the initial locale.
  const char *initial = nullptr;

  //  CONSTRUCTORS  //

  /// @brief Default locale options constructor.
  constexpr Options() = default;
};

} // namespace Talos::Locale

#endif
