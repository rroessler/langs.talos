#ifndef _FORGE_FLOW_EFFECT_HPP
#define _FORGE_FLOW_EFFECT_HPP

/// Forge Modules
#include "forge/forward/flow.hpp"

namespace Forge::Flow {

    /// @brief Potential Side-Effects.
    enum class Effect : uint8_t { NONE, BREAKS, LOOPS };

}  // namespace Forge::Flow

#endif
