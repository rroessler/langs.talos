#ifndef _XSIO_ASYNC_WATCHDOG_HPP
#define _XSIO_ASYNC_WATCHDOG_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"

namespace XSIO::Async {

    /// @brief Event Loop Watchdog.
    class Watchdog {
        //  PROPERTIES  //

        /// @brief Current clock value.
        $::Atomic<Timer::Point> m_clock;

        mutable $::Mutex::Auto m_mutex;  // Associated mutex.
        std::condition_variable m_cv;    // Condition variable.

        Manager* m_manager;          // Context to inherit.
        $::Thread::Handle m_thread;  // Heartbeat thread.

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Watchdog() = delete;

        /**
         * @brief Constructs a watchdog instance.
         * @param manager                   Asynchronous manager.
         */
        Watchdog(Manager* manager) : m_manager(manager), m_thread(&Watchdog::m_main, this) {}

        /// @brief Alert about join-failures before destruction.
        ~Watchdog() { $_ASSERT(!m_thread.joinable(), "Watchdog not joined before destruction"); }

        //  PUBLIC METHODS  //

        /// @brief Joins the underlying thread.
        void join();

       private:
        //  PRIVATE METHODS  //

        /// @brief Encapsulates running the watchdog thread.
        void m_main();
    };

}  // namespace XSIO::Async

#endif
