#ifndef _TALOS_MODULE_DYNAMIC_HPP
#define _TALOS_MODULE_DYNAMIC_HPP

/// Talos Includes
#include "talos/module/abstract.hpp"

namespace Talos::Module {

/// @brief Type Declaration Module.
struct Dynamic : public Mixin<Dynamic> {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Mixin::Mixin;

  //  PUBLIC METHODS  //

  /// @brief Gets the associated library name.
  inline constexpr $::String::View name() const noexcept { return resource().body(); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles interpreting a module.
   * @param isolate                   Runtime isolate.
   * @param exports                   Exports metadata.
   */
  Async::Thenable *m_interpret(Runtime::Isolate *isolate, Metadata::Wrapper<Phase::EXPORTED> *exports) final;
};

} // namespace Talos::Module

#endif
