#ifndef _XTDLIB_NOTATE_OPTIONS_HPP
#define _XTDLIB_NOTATE_OPTIONS_HPP

/// Library Includes
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/portable/stdlib.hpp"
#include "xtdlib/string/view.hpp"

namespace $::Notate {

/// @brief Notation Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Markdown fence value.
  String::View fence = "```";

  /// @brief Available named items.
  Map::Set<String::View> named = {};
};

} // namespace $::Notate

#endif
