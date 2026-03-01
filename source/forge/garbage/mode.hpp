#ifndef _FORGE_GARBAGE_MODE_HPP
#define _FORGE_GARBAGE_MODE_HPP

/// Forge Modules
#include "forge/forward/garbage.hpp"

namespace Forge::Garbage {

    /// @brief Potential Collection Modes
    enum class Mode : bool { MINOR, MAJOR };

}  // namespace Forge::Garbage

#endif
