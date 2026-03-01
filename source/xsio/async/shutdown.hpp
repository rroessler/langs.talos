#ifndef _XSIO_ASYNC_SHUTDOWN_HPP
#define _XSIO_ASYNC_SHUTDOWN_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"

namespace XSIO::Async {

    /// @brief Explicit Shutdown Handler.
    class Shutdown {
        //  PROPERTIES  //

        /// @brief Associated exit-code.
        int32_t m_errc = 0;

        /// @brief Current exited state.
        $::Atomic<bool> m_requested = false;

        $::Mutex::Auto &m_mutex;       // Bound mutex value.
        std::condition_variable m_cv;  // Condition variable.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a shutdown handler.
         * @param mutex                     Mutex to bind.
         */
        explicit Shutdown($::Mutex::Auto &mutex) : m_mutex(mutex) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the resulting exit-code.
        inline int32_t code() const noexcept { return m_errc; }

        /// @brief Gets the current flag state.
        inline bool state() const noexcept { return m_requested; }

        /// @brief Waits for flag to be released.
        inline void wait() {
            auto lock = $::Lock::scope(m_mutex);  // lock the state
            m_cv.wait(lock, [&] -> bool { return m_requested; });
        }

        /**
         * @brief Waits for a shutdown or duration to occur.
         * @param duration                  Duration to wait.
         */
        inline void wait(const Timer::Ticks &duration) {
            auto lock = $::Lock::scope(m_mutex);  // prepare the lock now
            m_cv.wait_for(lock, duration.underlying(), [&] -> bool { return m_requested; });
        }

        /**
         * @brief Notifies about the shutdown request.
         * @param exit_code                 Exit-code.
         */
        inline void request(int32_t exit_code = $_EXIT_SUCCESS) {
            if (m_notify()) m_shutdown(exit_code);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles notifying about the shutdown.
        inline bool m_notify() {
            auto lock = $::Lock::scope(m_mutex);  // lock the state
            bool first = m_requested.compare_exchange_strong(false, true);
            return lock.unlock(), m_cv.notify_all(), first;
        }

        /**
         * @brief Handles latching the exit state.
         * @param exit_code                 Exit-code.
         */
        inline void m_shutdown(int32_t exit_code) {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
            m_errc = exit_code;  // update the exit-code
        }
    };

}  // namespace XSIO::Async

#endif
