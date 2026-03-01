#ifndef _FORGE_FLOW_PASSABLE_HPP
#define _FORGE_FLOW_PASSABLE_HPP

/// Type Modules
#include "forge/flow/control.hpp"

namespace Forge::Flow {

    /// @brief Passable Control Flow.
    struct Passable : public Abstract<Passable> {
        //  CONSTRUCTORS  //

        /// @brief Constructs a passable flow state.
        explicit constexpr Passable() : Abstract<Passable>(-1) {}
    };

}  // namespace Forge::Flow

#endif
