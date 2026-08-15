#ifndef _XSIO_TIMER_TOKEN_HPP
#define _XSIO_TIMER_TOKEN_HPP

/// XSIO Includes
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"

namespace XSIO::Timer {

/// @brief Timer Cancellation Token.
class Token {
  //  PROPERTIES  //

  /// @brief Associated identifier.
  Identifier m_id = -1;

  /// @brief Runtime scheduler.
  Async::Scheduler *m_scheduler = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construction of tokens.
  explicit Token() = default;

  /**
   * @brief Constructs a cancellation token.
   * @param identifier                    Timer identifier.
   * @param scheduler                     Scheduler instance.
   */
  explicit Token(Identifier identifier, Async::Scheduler *scheduler) : m_id(identifier), m_scheduler(scheduler) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the timer-identifier.
  inline constexpr Identifier identifier() const noexcept { return m_id; }

  /// @brief Handles cancelling a timer.
  inline constexpr bool cancel() const noexcept { return m_cancel(); }

private:
  //  PRIVATE METHODS  //

  /// @brief Handles cancelling a token.
  bool m_cancel() const noexcept;
};

} // namespace XSIO::Timer

#endif
