#ifndef _XTEST_SESSION_PROGRESS_HPP
#define _XTEST_SESSION_PROGRESS_HPP

/// XT Modules
#include "xtest/forward/session.hpp"

namespace XT::Session {

    /// @brief Progress Value.
    struct Progress {
        size_t iter;              // Current iteration.
        size_t total;             // Total iterations.
        $::String::Buffer label;  // Progress label.
    };

}  // namespace XT::Session

#endif
