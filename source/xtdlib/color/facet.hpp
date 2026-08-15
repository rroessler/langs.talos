#ifndef _XTDLIB_COLOR_FACET_HPP
#define _XTDLIB_COLOR_FACET_HPP

/// Library Includes
#include "xtdlib/color/enabled.hpp"
#include "xtdlib/portable/stdlib.hpp"

namespace $::Color {

/// @brief Colored Facet Instance.
struct Facet final : public std::locale::facet {
  //  PROPERTIES  //

  /// @brief Coloring enablement.
  bool enabled = false;

  /// @brief Internally constructed ID.
  static std::locale::id id;

  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a colored locale.
   * @param stream                    Underlying stream.
   */
  constexpr Facet(std::ostream &os) : Facet(Enabled(os)) {}

  /**
   * @brief Constructs a colored locale.
   * @param stream                    Underlying stream.
   */
  constexpr Facet(std::ostream *os) : Facet(Enabled(*os)) {}

  /**
   * @brief Constructs a colored locale.
   * @param enabled                    Enablement state.
   */
  constexpr Facet(bool enabled) : std::locale::facet(0), enabled(enabled) {}
};

} // namespace $::Color

#endif
