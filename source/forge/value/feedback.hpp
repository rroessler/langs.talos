#ifndef _FORGE_VALUE_FEEDBACK_HPP
#define _FORGE_VALUE_FEEDBACK_HPP

/// Forge Includes
#include "forge/forward/value.hpp"

//  X-MACROS  //

/// @brief Internal Void Feedback.
#define XX_VALUES_FEEDBACK(X) \
    /**  NON-ERRORS  */       \
                              \
    X(ALL_OKAY)               \
    X(ITERATOR_SENTINEL)      \
                              \
    /**  EXCEPTIONS  */       \
                              \
    X(EXCEPTION_THROWN)       \
    X(ASYNC_TIMEOUT)          \
    X(FIELD_MISSING)          \
    X(FIELD_IMMUTABLE)

//  NAMESPACES  //

namespace Forge::Value {

    /// @brief Associated Feedback Values.
    $_XX_ENUM_CLASS(Feedback, uint8_t, XX_VALUES_FEEDBACK);

}  // namespace Forge::Value

//  UNDEFINES  //

#undef XX_VALUES_FEEDBACK

#endif
