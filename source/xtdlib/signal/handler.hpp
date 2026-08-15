#ifndef _XTDLIB_SIGNAL_HANDLER_HPP
#define _XTDLIB_SIGNAL_HANDLER_HPP

/// Library Includes
#include "xtdlib/lambda/unique.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"
#include "xtdlib/signal/code.hpp"

namespace $::Signal {

/// @brief Signal Callback Handler.
using Callback = Unique::Functor<void(const Code &) const>;

/// @brief Handles incoming signals.
class Handler {
  //  PROPERTIES  //

  /// @brief Associated mutex value.
  mutable Mutex::Auto m_mutex;

  /// @brief Currently bound signal callback.
  Callback m_callback = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a basic signal handler.
  explicit Handler() = default;

  /// @brief Removes all the attached signal handlers.
  ~Handler();

  //  PUBLIC METHODS  //

  /**
   * @brief Handles listening for a code.
   * @param code                    Signal to listen.
   */
  inline constexpr void listen(const Code &code) noexcept {
    $_UNUSED $_AUTO = Lock::guard(m_mutex);
    return m_listen(this, code); // listen
  }

  /**
   * @brief Handles listening for a code.
   * @param code                    Signal to ignore.
   */
  inline constexpr bool ignore(const Code &code) noexcept {
    $_UNUSED $_AUTO = Lock::guard(m_mutex);
    return m_ignore(this, code); // ignore
  }

  /**
   * @brief Handles attaching a signal handler.
   * @param callback                Callback to bind.
   */
  inline constexpr void attach(Callback &&callback) noexcept {
    $_UNUSED $_AUTO = Lock::guard(m_mutex);
    m_callback = std::move(callback); // bind
  }

  /**
   * @brief Handles raising a signal.
   * @param code                    Code to signal.
   */
  inline constexpr void raise(const Code &code) const noexcept {
    $_UNUSED $_AUTO = Lock::guard(m_mutex);
    if (m_callback) m_callback(code); // raise
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles attaching/detaching signals.
   * @param self                    Signal handler.
   * @param code                    Code to use.
   */
  static void m_listen(const Handler *self, const Code &code);
  static bool m_ignore(const Handler *self, const Code &code);
};

} // namespace $::Signal

#endif
