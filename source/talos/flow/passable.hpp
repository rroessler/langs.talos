#ifndef _TALOS_FLOW_PASSABLE_HPP
#define _TALOS_FLOW_PASSABLE_HPP

/// Type Includes
#include "talos/flow/control.hpp"

namespace Talos::Flow {

/// @brief Passable Control Flow.
struct Passable : public Mixin<Passable> {
  //  CONSTRUCTORS  //

  /// @brief Constructs a passable flow state.
  explicit constexpr Passable() : Mixin(-1) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Passable flows have no decernable effect.
  inline constexpr Effect m_effect() const noexcept final { return Effect::NONE; }
};

} // namespace Talos::Flow

#endif
