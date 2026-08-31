#ifndef _XTDLIB_SERDE_ESCAPE_HPP
#define _XTDLIB_SERDE_ESCAPE_HPP

/// Library Includes
#include "xtdlib/serde/value.hpp"

namespace $::Serde {

/**
 * @brief Handles escaping string escapes.
 * @param value                 Value to escape.
 */
Serde::Result<Serde::Text> Escape(const Text &value);
Serde::Result<Serde::Text> Escape(const String::View &value);

/**
 * @brief Handles unescaping string escapes.
 * @param value                 Value to unescape.
 */
Serde::Result<Serde::Text> Unescape(const Text &value);
Serde::Result<Serde::Text> Unescape(const String::View &value);

} // namespace $::Serde

#endif
