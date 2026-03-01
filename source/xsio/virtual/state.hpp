#ifndef _XSIO_VIRTUAL_STATE_HPP
#define _XSIO_VIRTUAL_STATE_HPP

/// XSIO Modules
#include "xsio/forward/virtual.hpp"

//  X-MACROS  //

#define XX_VIRTUAL_STATES(X) \
    X(CLEANED)               \
    X(WAITING)               \
    X(ACQUIRE)               \
    X(READY)                 \
    X(NATIVE)                \
    X(PAUSED)                \
    X(RECYCLE)               \
    X(WORKING)               \
    X(SHUTDOWN)

//  NAMESPACES  //

namespace XSIO::Virtual {

    /// @brief Available Virtual States.
    $_XX_ENUM_CLASS(State, uint8_t, XX_VIRTUAL_STATES);

}  // namespace XSIO::Virtual

//  UNDEFINES  //

#undef XX_VIRTUAL_STATES

#endif
