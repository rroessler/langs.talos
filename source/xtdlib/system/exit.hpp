#ifndef _XTDLIB_EXCEPTION_EXIT_HPP
#define _XTDLIB_EXCEPTION_EXIT_HPP

/// C++ Modules
#include <cstdlib>

/// Library Modules
#include "xtdlib/macros/attributes.hpp"

//  MACROS  //

#define $_EXIT_SUCCESS EXIT_SUCCESS
#define $_EXIT_FAILURE EXIT_FAILURE
#define $_EXIT_CUSTOM(N) 128 + (N)

//  PUBLIC METHODS  //

namespace $::System {

    //  PUBLIC METHODS  //

    /**
     * @brief Handles exit routines.
     * @param code                  Exit code to assign.
     */
    $_NORETURN $_INLINE_FORCE static void exit(int32_t code = $_EXIT_SUCCESS) { std::exit(code); }

}  // namespace $::System

#endif
