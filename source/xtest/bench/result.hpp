#ifndef _XTEST_BENCH_MEASURE_HPP
#define _XTEST_BENCH_MEASURE_HPP

/// Testing Includes
#include "xtest/forward/bench.hpp"

namespace XT::Bench {

/// @brief Measurement Result.
struct Result {
  size_t runs;    // Total runs taken.
  size_t sum;     // Total elapsed time.
  size_t mean;    // Mean time found.
  size_t minimum; // Minimum time found.
  size_t maximum; // Maximum time found.
  double stddev;  // Standard deviation.
};

} // namespace XT::Bench

#endif
