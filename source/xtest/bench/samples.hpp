#ifndef _XTEST_BENCH_SAMPLES_HPP
#define _XTEST_BENCH_SAMPLES_HPP

/// Testing Includes
#include "xtest/forward/bench.hpp"

namespace XT::Bench {

/// @brief Sampling Container.
struct Samples {
  size_t minimum = 10;   // Minimum count.
  size_t maximum = 5000; // Maximum count.
};

} // namespace XT::Bench

#endif
