#ifndef _XTEST_ASSERT_THAT_HPP
#define _XTEST_ASSERT_THAT_HPP

/// Testing Includes
#include "xtest/assert/failure.hpp"
#include "xtest/assert/info.hpp"
#include "xtest/forward/reporter.hpp"
#include "xtest/forward/session.hpp"
#include "xtest/trivia/location.hpp"

namespace XT::Assert {

/// @brief Assertions Manager.
class That {
  //  TYPEDEFS  //

  /// @brief Alias the location for easier use.
  using Details = Trivia::Location;

  /// @brief Allow reporters internal access.
  friend class Reporter::Abstract;

  //  PROPERTIES  //

  /// @brief Current assertion trace.
  Trace m_trace = {};

  /// @brief Pending assertion failures.
  Pending m_failures = {};

  /// @brief Assertion runner instance.
  Session::Runner *m_runner;

public:
  //  CONSTRUCTORS  //

  /// @brief Do not allow default construction.
  explicit That() = delete;

  /**
   * @brief Constructs an assertion factory.
   * @param runner                Runner to bind.
   */
  explicit That(Session::Runner *runner) : m_runner(runner) {}

  //  PUBLIC METHODS  //

  /**
   * @brief Constructs a set of assertion information.
   * @param message               Assertion message.
   * @param location              Assertion location.
   */
  inline constexpr Info info(const $::String::View &message) { return info(message, Details()); }
  inline constexpr Info info(const $::String::View &message, const Details &location) {
    return {.location = location, .message = message};
  }

  /**
   * @brief Constructs a set of assertion information.
   * @param label                 Assertion label.
   * @param message               Assertion message.
   */
  inline constexpr Info info(const $::String::View &label, const $::String::View &message) {
    return info(label, message, {});
  }

  /**
   * @brief Constructs a set of assertion information.
   * @param label                 Assertion label.
   * @param message               Assertion message.
   * @param location              Assertion location.
   */
  inline constexpr Info info(const $::String::View &label, const $::String::View &message, const Details &location) {
    return {.location = location, .message = message, .label = label};
  }

  /**
   * @brief Forces an immediate failure.
   * @param because               Optional message.
   * @param location              Assertion location.
   */
  inline bool fail(const $::String::View &because = "", const Details &location = {}) {
    return m_hook(false, info(because, location));
  }

  /**
   * @brief Checks if a value is truthy.
   * @param value                 Value to check.
   * @param because               Optional message.
   * @param location              Assertion location.
   */
  template <std::convertible_to<bool> T>
  inline bool okay(T value, const $::String::View &because = "", const Details &location = {}) {
    return m_hook(static_cast<bool>(value), info("okay", because, location));
  }

  /**
   * @brief Checks if two values are equal.
   * @param actual                Item to check.
   * @param expected              Expected value.
   * @param because               Optional message.
   * @param location              Assertion location.
   */
  template <class T, std::convertible_to<T> U>
  inline bool equal(T actual, U expected, const $::String::View &because = "", const Details &location = {}) {
    return m_hook(actual == static_cast<T>(expected), info("equals", because, location));
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles assertion hooks.
   * @param result                Assertion result.
   * @param info                  Assertion information.
   */
  bool m_hook(bool result, const Info &info);
};

} // namespace XT::Assert

#endif
