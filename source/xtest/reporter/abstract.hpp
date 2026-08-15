#ifndef _XTEST_REPORTER_ABSTRACT_HPP
#define _XTEST_REPORTER_ABSTRACT_HPP

/// Testing Includes
#include "xtest/assert/info.hpp"
#include "xtest/bench/mark.hpp"
#include "xtest/forward/session.hpp"
#include "xtest/handle/group.hpp"
#include "xtest/reporter/proxy.hpp"
#include "xtest/trivia/progress.hpp"
#include "xtest/trivia/statistics.hpp"

namespace XT::Reporter {

/// @brief Reporter Abstraction.
class $_ABSTRACT Abstract {
  //  TYPEDEFS  //

  /// @brief Allow session runners internal access.
  friend class Session::Runner;

protected:
  //  PROPERTIES  //

  /// @brief The associated session runner.
  Session::Runner *m_runner = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Only allow construction with a valid runner.
  constexpr Abstract() = delete;

  /**
   * @brief Constructs a reporter.
   * @param runner            Session runner.
   */
  constexpr Abstract(Session::Runner *runner) : m_runner(runner) {}

  /// @brief Virtual abstract destructor.
  virtual ~Abstract() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Before running hook.
   * @param sections          Total sections.
   * @param options           Testing options.
   */
  virtual void before_running($_UNUSED size_t sections, $_UNUSED const Session::Options *options) {}

  /**
   * @brief After running hook.
   * @param sections          Total sections.
   * @param elapsed           Elapsed duration.
   */
  virtual void after_running($_UNUSED size_t sections, $_UNUSED const $::Chrono::Duration &elapsed) {}

  /**
   * @brief Group opening hook.
   * @param group             Group starting.
   */
  virtual void group_opened($_UNUSED const Handle::Group *group) {}

  /**
   * @brief Group closing hook.
   * @param group             Group ending.
   */
  virtual void group_closed($_UNUSED const Handle::Group *group) {}

  /**
   * @brief Group failure hook.
   * @param group             Group failed.
   * @param reason            Failure reason.
   */
  virtual void group_failure($_UNUSED const Handle::Group *group, $_UNUSED const $::String::Buffer &reason) {}

  /**
   * @brief Test starting hook.
   * @param test              Test started.
   */
  virtual void test_starting($_UNUSED const Handle::Base *test) {}

  /**
   * @brief Test teardown hook.
   * @param test              Test finished.
   */
  virtual void test_teardown($_UNUSED const Handle::Base *test) {}

  /**
   * @brief Test successful hook.
   * @param test              Test finished.
   * @param duration          Test duration.
   */
  virtual void test_success($_UNUSED const Handle::Base *test, $_UNUSED const $::Chrono::Duration &duration) {}

  /**
   * @brief Test failed hook.
   * @param test              Test finished.
   * @param reason            Failure reason.
   */
  virtual void test_failure($_UNUSED const Handle::Base *test, $_UNUSED const $::String::Buffer &reason) {}

  /**
   * @brief Test timeout hook.
   * @param test              Test finished.
   * @param timeout           Timeout duration.
   */
  virtual void test_timeout($_UNUSED const Handle::Base *test, $_UNUSED const $::Chrono::Duration &timeout) {}

  /**
   * @brief Test skipped result.
   * @param test              Test skipped.
   */
  virtual void test_skipped($_UNUSED const Handle::Base *test) {}

  /**
   * @brief Test partial result.
   * @param test              Test unimplemented.
   */
  virtual void test_unimplemented($_UNUSED const Handle::Base *test) {}

  /**
   * @brief Test progress hook.
   * @param test              Test progressing.
   * @param progress          Progress update.
   */
  virtual void test_progress($_UNUSED const Handle::Base *test, $_UNUSED const Trivia::Progress &progress) {}

  /**
   * @brief Handles assertion startups.
   * @param assertion         Assertion information.
   */
  virtual void assertion_starting($_UNUSED const Assert::Info &assertion) {}

  /**
   * @brief Handles assertion teardowns.
   * @param assertion         Assertion information.
   * @param result            Assertion result flag.
   */
  virtual void assertion_teardown($_UNUSED const Assert::Info &assertion, $_UNUSED bool result) {}

  /**
   * @brief Handles assertion failures.
   * @param assertion         Assertion information.
   */
  virtual void assertion_failure($_UNUSED const Assert::Info &assertion) {}

  /**
   * @brief Benchmark finished hook.
   * @param bench             Benchmark finished.
   * @param result            Result of benchmark.
   */
  virtual void bench_finished($_UNUSED const Bench::Mark *bench, $_UNUSED const Bench::Result &result) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Gets a reference to the underlying stack-trace.
  Assert::Trace &m_trace();
  const Assert::Trace &m_trace() const;

  /// @brief Gets a reference to the statistics available.
  Trivia::Statistics &m_stats();
  const Trivia::Statistics &m_stats() const;

  /// @brief Gets a reference to the pending failures.
  Assert::Pending &m_pending();
  const Assert::Pending &m_pending() const;
};

} // namespace XT::Reporter

#endif
