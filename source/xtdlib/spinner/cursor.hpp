#ifndef _XTDLIB_SPINNER_CURSOR_HPP
#define _XTDLIB_SPINNER_CURSOR_HPP

/// Library Includes
#include "xtdlib/terminal/core.hpp"

namespace $::Spinner::Cursor {

/**
 * @brief Handles clearing cursors.
 * @param os                    Output stream.
 */
static inline constexpr void clear(std::ostream &os) {
  if (auto *fd = Terminal::as(os)) std::fputs("\033[K", fd);
}

/**
 * @brief Handles toggling cursors.
 * @param os                    Output stream.
 * @param state                 Cursor state.
 */
static inline constexpr void toggle(std::ostream &os, bool state) {
  if (auto *fd = Terminal::as(os)) std::fputs(state ? "\033[?25h" : "\033[?25l", fd);
}

} // namespace $::Spinner::Cursor

#endif
