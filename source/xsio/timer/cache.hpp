#ifndef _XSIO_TIMER_CACHE_HPP
#define _XSIO_TIMER_CACHE_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/timer/event.hpp"

namespace XSIO::Timer {

    /// @brief Timers Cache Instance.
    class Cache {
        //  PROPERTIES  //

        /// @brief Bound mutex value.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Bound scheduler instance.
        Async::Scheduler* m_scheduler;

        /// @brief Currently available events.
        std::vector<Event> m_events = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Cache() = delete;

        /**
         * @brief Constructs a timer-cache.
         * @param scheduler             Scheduler to bind.
         */
        explicit Cache(Async::Scheduler* scheduler) : m_scheduler(scheduler) {
            std::ranges::make_heap(m_events, Comparator());  // prepare heap
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the next available timestamp.
        inline Point next() {
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // lock the mutex now
            return m_events.empty() ? Point(0ns) : m_events.front().timestamp();
        }

        /**
         * @brief Handles cancelling a timer.
         * @param timer                 Identifier to cancel.
         */
        bool cancel(Identifier timer);

        /**
         * @brief Fires all eligible the timer events.
         * @param thread                Thread instance.
         * @param processor             Processor instance.
         */
        void fire(Virtual::Thread* thread, Virtual::Processor* processor);

        /**
         * @brief Suspends a thread until a timestamp.
         * @param thread                Thread to suspend.
         * @param timestamp             Timestamp to wait for.
         */
        void suspend(Virtual::Thread* thread, const Ticks& duration);
        void suspend(Virtual::Thread* thread, const Point& timestamp);

        /**
         * @brief Handles scheduling a timer-event.
         * @param duration              Duration to wait.
         * @param action                Timer action to be run.
         */
        Token schedule(const Ticks& duration, Callback callback);
        Token schedule(const Ticks& duration, $::Ptr::Unique<Action>&& action);

        /**
         * @brief Handles scheduling a timer-event.
         * @param timestamp             Timestamp to wait for.
         * @param action                Timer action to be run.
         */
        Token schedule(const Point& timestamp, Callback callback);
        Token schedule(const Point& timestamp, $::Ptr::Unique<Action>&& action);

       private:
        //  PRIVATE METHODS  //

        /// @brief Pops the top-most event.
        void m_pop();

        /**
         * @brief Pushes a timer-event.
         * @param timestamp             Timestamp to bind.
         * @param action                Timer action to run.
         */
        Token m_push(const Point& timestamp, $::Ptr::Unique<Action>&& action);
    };

}  // namespace XSIO::Timer

#endif
