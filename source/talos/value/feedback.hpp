#ifndef _TALOS_VALUE_FEEDBACK_HPP
#define _TALOS_VALUE_FEEDBACK_HPP

/// Talos Includes
#include "talos/forward/value.hpp"

namespace Talos::Value {

/// @brief Associated Feedback Values.
enum class Feedback : uint8_t {
  ALL_OKAY = 0b0000,
  ITER_SENTINEL = 0b0001,

  ERROR_THROWN = 0b1000,
  ASYNC_TIMEOUT = 0b1001,
  FIELD_MISSING = 0b1010,
  FIELD_IMMUTABLE = 0b1011,
};

} // namespace Talos::Value

#endif
