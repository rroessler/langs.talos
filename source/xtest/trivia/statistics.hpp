#ifndef _XTEST_TRIVIA_STATISTICS_HPP
#define _XTEST_TRIVIA_STATISTICS_HPP

/// Testing Includes
#include "xtest/forward/trivia.hpp"

namespace XT::Trivia {

/// @brief Statistics Container.
class Statistics {
  //  PROPERTIES  //

  size_t m_passed = 0;
  size_t m_failed = 0;
  size_t m_skipped = 0;
  size_t m_elapsed = 0;

public:
  //  CONSTRUCTORS  //

  /// @brief Default constructor.
  explicit Statistics() = default;

  //  PUBLIC METHODS  //

  inline constexpr size_t &passed() noexcept { return m_passed; }
  inline constexpr size_t passed() const noexcept { return m_passed; }

  inline constexpr size_t &failed() noexcept { return m_failed; }
  inline constexpr size_t failed() const noexcept { return m_failed; }

  inline constexpr size_t &skipped() noexcept { return m_skipped; }
  inline constexpr size_t skipped() const noexcept { return m_skipped; }

  inline constexpr size_t &elapsed() noexcept { return m_elapsed; }
  inline constexpr size_t elapsed() const noexcept { return m_elapsed; }

  inline constexpr bool success() const noexcept { return m_failed == 0; }
  inline constexpr size_t total() const noexcept { return m_passed + m_failed + m_skipped; }
};

} // namespace XT::Trivia

#endif
