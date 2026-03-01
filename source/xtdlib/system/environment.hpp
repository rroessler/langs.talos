#ifndef _XTDLIB_SYSTEM_ENVIRONMENT_HPP
#define _XTDLIB_SYSTEM_ENVIRONMENT_HPP

/// C++ Includes
#include <optional>

/// Library Includes
#include "xtdlib/container/map.hpp"
#include "xtdlib/string/buffer.hpp"

namespace $::Environment {

    //  PUBLIC METHODS  //

    /// @brief Gets a view of the current variables.
    $::Dict<String::Buffer> view();

    /**
     * @brief Gets a singular variable.
     * @param key               Key to get.
     */
    std::optional<String::Buffer> get(const String::Buffer& key);

    /**
     * @brief Removes a singular variable.
     * @param key               Key to set.
     */
    bool del(const String::Buffer& key);

    /**
     * @brief Sets a singular variable.
     * @param key               Key to set.
     * @param value             Value to set.
     */
    bool set(const String::Buffer& key, const String::Buffer& value);

}  // namespace $::Environment

#endif
