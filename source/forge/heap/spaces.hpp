#ifndef _FORGE_HEAP_SPACES_HPP
#define _FORGE_HEAP_SPACES_HPP

/// Forge Modules
#include "forge/heap/region.hpp"

namespace Forge::Heap {

    /// @brief Encapsulates Heap Regions.
    struct Spaces {
        //  PROPERTIES  //

        $::Set<Region*> free = {};      // Acquirable regions.
        $::Set<Region*> mapped = {};    // Memory mapped regions.
        $::Set<Region*> unmapped = {};  // Unmapped memory regions.

        $::Set<Region*> eden = {};    // Newly created regions.
        $::Set<Region*> junior = {};  // Survived one GC cycle.
        $::Set<Region*> senior = {};  // Survived multiple GC cycles.
        $::Set<Region*> stacks = {};  // Stack frame regions.

        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit Spaces() = default;
    };

}  // namespace Forge::Heap

#endif
