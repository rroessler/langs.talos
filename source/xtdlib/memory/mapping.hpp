#ifndef _XTDLIB_MEMORY_MAPPING_HPP
#define _XTDLIB_MEMORY_MAPPING_HPP

/// Library Includes
#include "xtdlib/debug/assert.hpp"

namespace $::Memory::Prot {

//  PROPERTIES  //

extern int32_t NONE;
extern int32_t READ;
extern int32_t WRITE;
extern int32_t EXEC;

} // namespace $::Memory::Prot

namespace $::Memory::Flag {

//  PROPERTIES  //

extern int32_t FIXED;
extern int32_t PRIVATE;
extern int32_t SHARED;
extern int32_t ANONYMOUS;
extern int32_t DEFAULT;

} // namespace $::Memory::Flag

namespace $::Memory::Page {

//  PUBLIC METHODS  //

/// @brief Gets the underlying system page-size.
size_t size();

/**
 * @brief Checks if a given size is page-aligned.
 * @param _                    Size to validate.
 */
inline constexpr size_t aligned($_UNUSED size_t _) { return $_ASSERT(_ % size() == 0), _; }

/**
 * @brief Checks if a given size is page-aligned.
 * @param _                     Size to validate.
 */
inline constexpr size_t validate($_UNUSED size_t _) { return $_ASSERT(_ >= size()), aligned(_); }

} // namespace $::Memory::Page

namespace $::Memory::Map {

//  PUBLIC METHODS  //

/**
 * @brief Handles freeing mapped memory.
 * @param address               Address to free.
 * @param size                  Memory size to free.
 */
void free(void *address, size_t size);

/**
 * @brief Updates mapped memory protections.
 * @param address               Address to update.
 * @param size                  Memory size to update.
 * @param prot                  Protection to bind.
 */
bool protect(void *address, size_t size, int32_t prot);

/**
 * @brief Allocates anonymous mapped memory.
 * @param size                  Size of memory.
 * @param prot                  Protection to bind.
 * @param flags                 Memory flags to bind.
 */
void *alloc(size_t size, int32_t prot = Prot::NONE, int32_t flags = Flag::DEFAULT);

/**
 * @brief Allocates mapped memory at an address.
 * @param address               Address to map.
 * @param size                  Size of memory.
 * @param prot                  Protection to bind.
 * @param flags                 Memory flags to bind.
 */
void *alloc(void *address, size_t size, int32_t prot = Prot::NONE, int32_t flags = Flag::DEFAULT);

} // namespace $::Memory::Map

#endif
