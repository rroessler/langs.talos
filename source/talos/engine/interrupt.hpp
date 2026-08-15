#ifndef _TALOS_ENGINE_INTERRUPT_HPP
#define _TALOS_ENGINE_INTERRUPT_HPP

/// Talos Includes
#include "talos/forward/engine.hpp"

namespace Talos::Engine {

/// @brief Available Interrupt Modes.
enum class Interrupt : uint8_t {
  BAILOUT, // Forces a bailout.
  DISPOSE, // Flags disposables.
};

} // namespace Talos::Engine

#endif
