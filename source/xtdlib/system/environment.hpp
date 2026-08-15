#ifndef _XTDLIB_SYSTEM_ENVIRON_HPP
#define _XTDLIB_SYSTEM_ENVIRON_HPP

/// Library Includes
#include "xtdlib/container/map.hpp"
#include "xtdlib/string/buffer.hpp"

namespace $::Environ {

//  PUBLIC METHODS  //

/// @brief Gets a view of the current variables.
$::Map::Dict<String::Buffer> view();

/**
 * @brief Gets a singular variable.
 * @param key               Key to get.
 */
std::optional<String::Buffer> get(const String::Buffer &key);

/**
 * @brief Removes a singular variable.
 * @param key               Key to set.
 */
bool del(const String::Buffer &key);

/**
 * @brief Sets a singular variable.
 * @param key               Key to set.
 * @param value             Value to set.
 */
bool set(const String::Buffer &key, const String::Buffer &value);

} // namespace $::Environ

#endif
