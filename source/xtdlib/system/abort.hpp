#ifndef _XTDLIB_SYSTEM_ABORT_HPP
#define _XTDLIB_SYSTEM_ABORT_HPP

/// Library Includes
#include "xtdlib/macros/attributes.hpp"
#include "xtdlib/portable/stdlib.hpp"

namespace $::System {

/// @brief Internal abort handler.
$_NORETURN $_INLINE_FORCE static void abort() { std::abort(); }

} // namespace $::System

#endif
