#ifndef _XTEST_ASSERT_FAILURE_HPP
#define _XTEST_ASSERT_FAILURE_HPP

/// Testing Includes
#include "xtest/forward/assert.hpp"
#include "xtest/forward/session.hpp"

namespace XT::Assert {

/// @brief Assertion Failure Value.
struct Failure {
  Trace trace;              // Stack-trace.
  $::String::View title;    // Test title.
  $::String::Buffer reason; // Failure reason.
};

} // namespace XT::Assert

#endif
