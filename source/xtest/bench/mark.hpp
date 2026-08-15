#ifndef _XTEST_BENCH_MARK_HPP
#define _XTEST_BENCH_MARK_HPP

/// Testing Includes
#include "xtest/bench/result.hpp"
#include "xtest/handle/mixin.hpp"

namespace XT::Bench {

/// @brief Encapsulates a Benchmark Test.
class Mark : public Handle::Mixin<Mark> {
  //  PROPERTIES  //

  /// @brief The callback for benchmarking.
  Handle::Callback m_callback = [](Session::Runner *) {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a benchmark test.
   * @param title               Title of test.
   * @param callback            Benchmark callback.
   */
  constexpr Mark(const $::String::Buffer &title, Handle::Callback &&callback) : Mark(title, {}, std::move(callback)) {}

  /**
   * @brief Constructs a benchmark test.
   * @param title               Title of test.
   * @param location            Test location.
   * @param callback            Benchmark callback.
   */
  constexpr Mark(const $::String::Buffer &title, const Trivia::Location &location, Handle::Callback &&callback)
      : Mixin(title, location), m_callback(std::move(callback)) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Gets the total count of the benchmark.
  size_t m_count() const noexcept final;

  /**
   * @brief Handles running the callback.
   * @param runner                Test runner.
   */
  void m_execute(Session::Runner *runner) const final;

  /**
   * @brief Handles analyzing results.
   * @param timings               Timings to analyze.
   */
  Result m_analyze(const Timings &timings) const;

  /**
   * @brief Handles running warmups.
   * @param runner                Test runner.
   * @param iterations            Warmup iterations.
   */
  void m_warmup(Session::Runner *runner, size_t iterations) const;

  /**
   * @brief Handles executing measurements.
   * @param runner                Test runner.
   * @param timeout               Total timeout.
   * @param samples               Minimum samples.
   */
  Timings m_measure(Session::Runner *runner, size_t timeout, const Samples &samples) const;
};

} // namespace XT::Bench

#endif
