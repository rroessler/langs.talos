#ifndef _XTDLIB_GLOB_PATTERN_HPP
#define _XTDLIB_GLOB_PATTERN_HPP

/// Vendor Includes
#include <aster/aster.hpp>

/// Library Includes
#include "xtdlib/string/view.hpp"

namespace $::Glob {

/// @brief Globbing Options Available.
using Options = Aster::Options;

/// @brief Underlying Glob Iterator.
using Iterator = Aster::Iterator;

/// @brief Available Globbing File-Types.
using Archetype = Aster::Archetype;

/// @brief A glob pattern instance.
struct Pattern : public Aster::Pattern {
  //  TYPEDEFS  //

  /// @brief Inherit the baseline constructor.
  using Aster::Pattern::Pattern;

  //  PUBLIC METHODS  //

  /**
   * @brief Attempts iterating a glob-pattern.
   * @param options               Iteration options.
   */
  inline constexpr Iterator iterate(const Options &options = {}) const noexcept { return ++Iterator(this, options); }
};

} // namespace $::Glob

#endif
