#ifndef _XTEST_ASSERT_INFO_HPP
#define _XTEST_ASSERT_INFO_HPP

/// Testing Includes
#include "xtest/trivia/location.hpp"

namespace XT::Assert {

/// @brief Assertion Info Value.
struct Info {
  Trivia::Location location;      // Assertion location.
  $::String::View message;        // Optional message.
  $::String::View label = "fail"; // Assertion label.
};

} // namespace XT::Assert

#endif
