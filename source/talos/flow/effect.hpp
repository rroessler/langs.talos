#ifndef _TALOS_FLOW_EFFECT_HPP
#define _TALOS_FLOW_EFFECT_HPP

/// Talos Includes
#include "talos/forward/flow.hpp"

namespace Talos::Flow {

/// @brief Potential Side-Effects.
enum class Effect : uint8_t { NONE, BREAKS, LOOPS };

} // namespace Talos::Flow

#endif
