#ifndef _XTEST_BENCH_OPTIONS_HPP
#define _XTEST_BENCH_OPTIONS_HPP

/// Testing Includes
#include "xtest/bench/samples.hpp"

namespace XT::Bench {

/// @brief Benchmarking Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Denotes whether enabled or not.
  bool enabled = false;

  /// @brief Declare a warmup amount.
  size_t warmup = 0;

  /// @brief Minimum samples expected.
  Samples samples = {};

  /// @brief Prepare an expected timeout.
  $::Chrono::Duration timeout = 5s;
};

} // namespace XT::Bench

#endif
