#ifndef _XTDLIB_MACROS_FORWARD_HPP
#define _XTDLIB_MACROS_FORWARD_HPP

//  MACROS  //

/// @brief Forward declares namespaced types/values.
#define $_FWD(N, ...)          \
  namespace N { __VA_ARGS__; }

#endif
