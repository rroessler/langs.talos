#ifndef _FORGE_GARBAGE_OPTIONS_HPP
#define _FORGE_GARBAGE_OPTIONS_HPP

/// Forge Modules
#include "forge/garbage/mode.hpp"

namespace Forge::Garbage {

    /// @brief Potential garbage Options.
    struct Options {
        //  PROPERTIES  //

        size_t force_cycle = 16;         // Force major GC every "nth" cycle.
        double ratio_threshold = 0.25f;  // Free/Mapped regions ratio trigger.

        $::Chrono::Duration minor_grow_rate = 5 * 1000;     // Growth rate for minor GC [ms].
        $::Chrono::Duration major_grow_rate = 500;          // Growth rate for major GC [ms].
        $::Chrono::Duration major_shrink_rate = 30 * 1000;  // Shrink rate for major GC [ms].

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of options.
        constexpr Options() = default;
    };

}  // namespace Forge::Garbage

#endif
