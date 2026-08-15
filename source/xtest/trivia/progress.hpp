#ifndef _XTEST_TRIVIA_PROGRESS_HPP
#define _XTEST_TRIVIA_PROGRESS_HPP

/// Testing Includes
#include "xtest/forward/trivia.hpp"

namespace XT::Trivia {

/// @brief Progress Value.
struct Progress {
  size_t iter;             // Current iteration.
  size_t total;            // Total iterations.
  $::String::Buffer label; // Progress label.
};

} // namespace XT::Trivia

#endif
