#ifndef _FORGE_HEAP_OPTIONS_HPP
#define _FORGE_HEAP_OPTIONS_HPP

/// Forge Includes
#include "forge/heap/limits.hpp"
#include "forge/value/pointer.hpp"

namespace Forge::Heap::Limits {}

namespace Forge::Heap {

    /// @brief Heap Address Typing.
    using Address = Pointer::Underlying;

    /// @brief Heap Options.
    struct Options {
        //  PROPERTIES  //

        size_t garbage_attempts = 4;    // GC attempts allowed.
        size_t garbage_survivors = 15;  // Senior survivor count.

        float growth_factor = 1.5f;  // Default heap growth factor.
        float shrink_factor = 0.5f;  // Default heap shrink factor.

        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted set of options.
        constexpr Options() = default;
    };

}  // namespace Forge::Heap

#endif
