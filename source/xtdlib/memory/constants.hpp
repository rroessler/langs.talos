#ifndef _XTDLIB_MEMORY_CONSTANTS_HPP
#define _XTDLIB_MEMORY_CONSTANTS_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Memory::Size {

//  PROPERTIES  //

static inline constexpr size_t KB = 1024;    // Kibibyte/Kilobyte value.
static inline constexpr size_t MB = KB * KB; // Mebibyte/Megabyte value.
static inline constexpr size_t GB = KB * MB; // Gibibyte/Gigabyte value.
static inline constexpr size_t TB = KB * GB; // Tebibyte/Terabyte value.
static inline constexpr size_t PB = KB * TB; // Pebibyte/Petabyte value.

/// @brief Gets the size of pointers.
static inline constexpr size_t PTR = sizeof(uintptr_t);

} // namespace $::Memory::Size

#endif
