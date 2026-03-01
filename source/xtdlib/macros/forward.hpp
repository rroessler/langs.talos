#ifndef _XTDLIB_MACROS_FORWARD_HPP
#define _XTDLIB_MACROS_FORWARD_HPP

//  MACROS  //

/// @brief Allows constructing a forward declaration macro.
#define $_FWD(D, ...)       \
    namespace __VA_ARGS__ { \
        D;                  \
    }

#endif
