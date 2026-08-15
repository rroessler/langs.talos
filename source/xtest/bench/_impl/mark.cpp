/// Testing Includes
#include "xtest/bench/mark.hpp"
#include "xtest/assert/reason.hpp"
#include "xtest/session/runner.hpp"

//  PRIVATE METHODS  //

size_t XT::Bench::Mark::m_count() const noexcept { return 1; }

void XT::Bench::Mark::m_execute(Session::Runner *runner) const {
  // destructure some common items now
  auto *reporter = runner->reporter();
  auto *options = &runner->options()->bench;

  // if skipping then declare as such now
  reporter->test_starting(this);

  // skip when necessary to do so
  if (trivia()->todo) return reporter->test_unimplemented(this);
  if (trivia()->skip || !options->enabled) return reporter->test_skipped(this);

  auto samples = options->samples; // get some details to be used
  auto timeout = static_cast<size_t>(options->timeout.count());

  try {
    // warmup the callback as necessary
    m_warmup(runner, options->warmup);

    // get the measurements
    auto timings = m_measure(runner, timeout, samples);
    auto result = m_analyze(timings); // analyze them

    // declare as a success now
    reporter->bench_finished(this, result);
  }

  catch (...) {
    reporter->test_failure(this, Assert::Reason());
  }
}

void XT::Bench::Mark::m_warmup(Session::Runner *runner, size_t iterations) const {
  for (size_t ii = 0; ii < iterations; ++ii) {
    runner->reporter()->test_progress(this, {ii, iterations, "Warmup"});
    m_callback(runner); // and run the callback now as necessary
  }
}

XT::Bench::Timings XT::Bench::Mark::m_measure(Session::Runner *runner, size_t timeout, const Samples &samples) const {
  // run an initial timing run now to determine sample iterations
  size_t initial = $::Clock::Measure([&] { m_callback(runner); }).count();
  auto iterations = std::max(timeout / initial, samples.minimum);
  iterations = std::min(iterations, samples.maximum) - 1; // resolve

  // prepare the initial timing to be used now
  auto timings = Timings({initial});

  // attempt running our callback as many times now
  for (size_t ii = 0; ii < iterations; ++ii) {
    runner->reporter()->test_progress(this, {ii, iterations, "Benchmark"});
    timings.emplace_back($::Clock::Measure([&] { m_callback(runner); }).count());
  }

  // return the sorted results now
  return timings;
}

XT::Bench::Result XT::Bench::Mark::m_analyze(const Timings &timings) const {
  // get the total runs and mean to be used
  auto sum = std::ranges::fold_left(timings, 0, std::plus{});
  auto runs = timings.size(), mean = sum / timings.size();

  // get the available minimum and maximum
  auto minimum = std::ranges::min(timings), maximum = std::ranges::max(timings);

  // get the summed square of all values
  auto square = std::ranges::fold_left(timings, 0, [mean](double a, double x) { return a + std::pow(x - mean, 2); });

  // construct the standard-deviation now
  auto stddev = runs < 2 ? 0 : std::sqrt(square / (runs - 1));

  // construct the final result now
  return {
      .runs = runs,
      .sum = sum,
      .mean = mean,
      .minimum = minimum,
      .maximum = maximum,
      .stddev = stddev,
  };
}
