#ifndef _XTEST_ASSERT_FAILURE_HPP
#define _XTEST_ASSERT_FAILURE_HPP

/// XT Modules
#include "xtest/forward/assert.hpp"
#include "xtest/forward/session.hpp"

namespace XT::Assert {

    /// @brief Assertion Failure Value.
    struct Failure {
        Trace trace;               // Stack-trace.
        $::String::View title;     // Test title.
        $::String::Buffer reason;  // Failure reason.
    };

    /// @brief Pending Failures.
    using Pending = std::vector<Failure>;

}  // namespace XT::Assert

#endif
