#ifndef _TALOS_HEAP_OPTIONS_HPP
#define _TALOS_HEAP_OPTIONS_HPP

/// Talos Includes
#include "talos/heap/limits.hpp"
#include "talos/value/pointer.hpp"

namespace Talos::Heap {

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

}  // namespace Talos::Heap

#endif
