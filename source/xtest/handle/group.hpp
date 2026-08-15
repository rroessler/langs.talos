#ifndef _XTEST_HANDLE_GROUP_HPP
#define _XTEST_HANDLE_GROUP_HPP

/// Testing Includes
#include "xtest/handle/mixin.hpp"

namespace XT::Handle {

/// @brief Initializer list for groups.
using Initializer = std::initializer_list<const Base *>;

/// @brief Encapsulates a Grouped Tests.
class Group : public Mixin<Group> {
  //  PROPERTIES  //

  /// @brief The setup handler.
  Handle::Callback m_setup = nullptr;

  /// @brief Bound Group Tests.
  std::vector<const Base *> m_tests = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Inherit the base mixin constructor.
  using Mixin::Mixin;

  //  PUBLIC METHODS  //

  /// @brief Gets all the associated group tests.
  inline constexpr const std::vector<const Base *> &tests() const noexcept { return m_tests; }

  /**
   * @brief Handles binding unit tests.
   * @param list                      Initializer list.
   */
  inline constexpr Group *bind(const Base *test) { return m_tests = {test}, this; }
  inline constexpr Group *bind(const Initializer &list) { return m_tests = list, this; }
  inline constexpr Group *bind(Callback &&setup) { return m_setup = std::move(setup), this; }

  /**
   * @brief Handles emplacing unit tests.
   * @param list                      Initializer list.
   */
  inline constexpr Group *emplace(const Base *test) { return m_tests.emplace_back(test), this; }
  inline constexpr Group *emplace(const Initializer &list) { return $::Ranges::Append(m_tests, list), this; }

protected:
  //  PRIVATE METHODS  //

  /// @brief Gets the total count of the benchmark.
  size_t m_count() const noexcept final;

  /**
   * @brief Handles initializing groups.
   * @param runner                    Test runner.
   */
  bool m_initialize(Session::Runner *runner) const;

  /**
   * @brief Handles running the callback.
   * @param runner                Test runner.
   */
  void m_execute(Session::Runner *runner) const final;
};

} // namespace XT::Handle

#endif
