#ifndef _XTDLIB_SYSTEM_ABORT_HPP
#define _XTDLIB_SYSTEM_ABORT_HPP

/// C++ Modules
#include <cstdlib>

/// Library Modules
#include "xtdlib/macros/attributes.hpp"

namespace $::System {

    //  PUBLIC METHODS  //

    /// @brief Internal abort handler.
    $_NORETURN $_INLINE_FORCE static void abort() { std::abort(); }

}  // namespace $::System

#endif
