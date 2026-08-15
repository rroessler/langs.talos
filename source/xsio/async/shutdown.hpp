#ifndef _XSIO_ASYNC_SHUTDOWN_HPP
#define _XSIO_ASYNC_SHUTDOWN_HPP

/// XSIO Includes
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"

namespace XSIO::Async {

/// @brief Explicit Shutdown Handler.
class Shutdown {
  //  PROPERTIES  //

  /// @brief Associated exit-code.
  int32_t m_errc = 0;

  /// @brief The requested exit signaller.
  $::Async::Signaller m_requested;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a shutdown handler.
   * @param mutex                     Mutex to bind.
   */
  explicit Shutdown($::Mutex::Auto &mutex) : m_requested(mutex) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the resulting exit-code.
  inline int32_t code() const noexcept { return m_errc; }

  /// @brief Gets the current flag state.
  inline bool state() const noexcept { return m_requested.state(); }

  /// @brief Waits for flag to be released.
  inline void wait() { m_requested.wait(); }

  /**
   * @brief Waits for a shutdown or duration to occur.
   * @param duration                  Duration to wait.
   */
  inline void wait(const Timer::Ticks &duration) { m_requested.wait(duration); }

  /**
   * @brief Notifies about the shutdown request.
   * @param exit_code                 Exit-code.
   */
  inline void request(int32_t exit_code = EXIT_SUCCESS) {
    if (m_requested.notify()) m_shutdown(exit_code);
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles latching the exit state.
   * @param exit_code                 Exit-code.
   */
  inline void m_shutdown(int32_t exit_code) {
    $_UNUSED $_AUTO = m_requested.guard();
    m_errc = exit_code; // update exit-code
  }
};

} // namespace XSIO::Async

#endif
