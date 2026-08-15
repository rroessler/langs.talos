#ifndef _XJCT_ARCHIVE_OPTIONS_HPP
#define _XJCT_ARCHIVE_OPTIONS_HPP

/// XJCT Modules
#include "xjct/archive/format.hpp"

namespace XJCT::Imbue {

/// @brief Imbue Options Structure.
struct Options {
  //  PROPERTIES  //

  /// @brief Name of resource.
  Archive::Section name = "";

  /// @brief Data to be emplaced.
  Blob::View blob = "";

  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted set of options.
  constexpr Options() = default;

  /**
   * @brief Constructs imbuement options.
   * @param name              Name of resource.
   */
  constexpr Options(const $::String::View &name) : name(name) {}

  /**
   * @brief Constructs imbuement options.
   * @param name              Name of resource.
   * @param blob              Blob to imbue.
   */
  constexpr Options(const $::String::View &name, const Blob::View &blob) : name(name), blob(blob) {}
};

} // namespace XJCT::Imbue

#endif
