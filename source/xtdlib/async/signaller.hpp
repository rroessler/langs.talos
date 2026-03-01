#ifndef _XTDLIB_ASYNC_SIGNALLER_HPP
#define _XTDLIB_ASYNC_SIGNALLER_HPP

/// C++ Modules
#include <condition_variable>

/// Library Includes
#include "xtdlib/async/atomic.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"

namespace $ {

    /// @brief Wait Flag Implementation.
    class Signaller {
        //  PROPERTIES  //

        Mutex::Auto &m_mutex;
        std::condition_variable m_cv;
        Atomic<bool> m_state = false;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an atomic flag.
         * @param mutex                 Mutex to encapsulate.
         */
        explicit Signaller(Mutex::Auto &mutex) : m_mutex(mutex) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the current flag state.
        inline bool state() const noexcept { return m_state; }

        /// @brief Waits for flag to be released.
        inline void wait() {
            auto lock = Lock::scope(m_mutex);  // lock the state
            m_cv.wait(lock, [&]() -> bool { return m_state; });
        }

        /// @brief Signals semaphore completion.
        inline bool notify() {
            auto lock = Lock::scope(m_mutex);  // lock the state
            bool first = m_state.compare_exchange_strong(false, true);
            return lock.unlock(), m_cv.notify_all(), first;
        }

        /// @brief Resets semaphore state.
        inline bool reset() {
            auto lock = Lock::scope(m_mutex);  // lock the state
            bool first = m_state.compare_exchange_strong(true, false);
            return lock.unlock(), m_cv.notify_all(), first;
        }
    };

}  // namespace $

#endif