#ifndef _XTDLIB_UTILITY_NEVER_HPP
#define _XTDLIB_UTILITY_NEVER_HPP

/// Library Modules
#include "xtdlib/macros/attributes.hpp"

namespace $ {

    /// @brief Ensures inheritors can never be constructed.
    struct $_ABSTRACT Never {
        //  CONSTRUCTORS  //

        constexpr Never(...) = delete;
        constexpr ~Never() = delete;

        //  OPERATOR METHODS  //

        inline constexpr Never& operator=(Never&&) = delete;
        inline constexpr Never& operator=(const Never&) = delete;
    };

}  // namespace $

#endif
