#ifndef _XSIO_ASYNC_WATCHDOG_HPP
#define _XSIO_ASYNC_WATCHDOG_HPP

/// XSIO Includes
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"

namespace XSIO::Async {

/// @brief Event Loop Watchdog.
class Watchdog {
  //  PROPERTIES  //

  /// @brief Associated mutex.
  mutable $::Mutex::Auto m_mutex;

  /// @brief Current clock value.
  $::Async::Atomic<Timer::Point> m_clock;

  Manager *m_runtime;   // Runtime manager.
  std::thread m_thread; // Heartbeat thread.

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a watchdog instance.
   * @param runtime                   Asynchronous runtime.
   */
  explicit Watchdog();
  explicit Watchdog(Manager *runtime);

  /// @brief Alert about join-failures before destruction.
  ~Watchdog();

  //  PUBLIC METHODS  //

  /// @brief Joins the underlying thread.
  void join();

private:
  //  PRIVATE METHODS  //

  /// @brief Encapsulates running the watchdog thread.
  void m_main();
};

} // namespace XSIO::Async

#endif
