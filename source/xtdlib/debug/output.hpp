#ifndef _XTDLIB_IO_PRINT_HPP
#define _XTDLIB_IO_PRINT_HPP

/// Library Includes
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"

//  X-MACROS  //

/// @brief Available Printing Functions.
#define XX_PRINTERS(X, S) \
  X(S, , stdout)          \
  X(S, e, stderr)

//  NAMESPACES  //

namespace $::Debug {

//  PUBLIC METHODS  //

/// @brief Handles constructing an IO lock.
static inline Mutex::Guard<Mutex::Recursive> acquire() {
  static auto s_mutex = Mutex::Recursive();
  return Lock::guard(s_mutex); // and lock
}

/// @brief Handles printing a stdout line.
static inline void println() {
  $_UNUSED $_AUTO = acquire();
  fmt::println(stdout, "");
}

/// @brief Handles printing a stderr line.
static inline void eprintln() {
  $_UNUSED $_AUTO = acquire();
  fmt::println(stderr, "");
}

#define X(S, N, F, ...)                                                                  \
  template <class T> void N##print##S(const T &value) {                                  \
    $_UNUSED $_AUTO = acquire();                                                         \
    fmt::print##S(F, "{0}", value);                                                      \
  }                                                                                      \
                                                                                         \
  template <class... As> void N##print##S(fmt::format_string<As...> fmt, As &&...args) { \
    $_UNUSED $_AUTO = acquire();                                                         \
    fmt::print##S(F, fmt, std::forward<As>(args)...);                                    \
  }

XX_PRINTERS(X, )
XX_PRINTERS(X, ln)
#undef X

} // namespace $::Debug

//  UNDEFINES  //

#undef XX_PRINTERS

#endif
