#ifndef _TALOS_FLOW_PASSABLE_HPP
#define _TALOS_FLOW_PASSABLE_HPP

/// Type Modules
#include "talos/flow/control.hpp"

namespace Talos::Flow {

    /// @brief Passable Control Flow.
    struct Passable : public Abstract<Passable> {
        //  CONSTRUCTORS  //

        /// @brief Constructs a passable flow state.
        explicit constexpr Passable() : Abstract<Passable>(-1) {}
    };

}  // namespace Talos::Flow

#endif
