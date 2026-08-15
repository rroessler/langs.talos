#ifndef _TALOS_HEAP_STORAGE_HPP
#define _TALOS_HEAP_STORAGE_HPP

/// Talos Includes
#include "talos/heap/region.hpp"

namespace Talos::Heap {

/// @brief Encapsulates Available Heap Regions.
struct Storage {
  //  PROPERTIES  //

  $::Map::Set<Region *> free = {};     // Acquirable regions.
  $::Map::Set<Region *> mapped = {};   // Memory mapped regions.
  $::Map::Set<Region *> unmapped = {}; // Unmapped memory regions.

  $::Map::Set<Region *> eden = {};   // Newly created regions.
  $::Map::Set<Region *> junior = {}; // Survived one GC cycle.
  $::Map::Set<Region *> senior = {}; // Survived multiple GC cycles.
  $::Map::Set<Region *> stacks = {}; // Stack frame regions.

  //  CONSTRUCTORS  //

  /// @brief Default constructor.
  explicit Storage() = default;
};

} // namespace Talos::Heap

#endif
