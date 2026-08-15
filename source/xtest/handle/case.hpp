#ifndef _XTEST_HANDLE_CASE_HPP
#define _XTEST_HANDLE_CASE_HPP

/// Testing Includes
#include "xtest/handle/mixin.hpp"

namespace XT::Handle {

/// @brief Encapsulates a Basic Test.
class Case : public Mixin<Case> {
  //  PROPERTIES  //

  /// @brief The callback for benchmarking.
  Callback m_callback = [](Session::Runner *) {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a test-case.
   * @param title               Title of test.
   * @param callback            Benchmark callback.
   */
  constexpr Case(const $::String::Buffer &title, Callback &&callback) : Case(title, {}, std::move(callback)) {}

  /**
   * @brief Constructs a test-case.
   * @param title               Title of test.
   * @param location            Test location.
   * @param callback            Benchmark callback.
   */
  constexpr Case(const $::String::Buffer &title, const Trivia::Location &location, Callback &&callback)
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
};

} // namespace XT::Handle

#endif
