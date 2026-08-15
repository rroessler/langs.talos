#ifndef _TALOS_MODULE_BINARY_HPP
#define _TALOS_MODULE_BINARY_HPP

/// Talos Includes
#include "talos/forward/image.hpp"
#include "talos/module/abstract.hpp"

namespace Talos::Module {

/// @brief Bundled Archive Module.
struct Archive : public Mixin<Archive> {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructors.
  using Mixin::Mixin;

  /**
   * @brief Constructs a module from a compilation archive.
   * @param arena                     Archive arena.
   */
  explicit Archive($::Unique::Pointer<Image::Arena> &&arena);
  explicit Archive(XI::Container *services, $::Unique::Pointer<Image::Arena> &&arena);
};

} // namespace Talos::Module

#endif
