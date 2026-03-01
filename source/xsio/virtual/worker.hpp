#ifndef _XSIO_VIRTUAL_WORKER_HPP
#define _XSIO_VIRTUAL_WORKER_HPP

/// XSIO Modules
#include "xsio/async/loop.hpp"
#include "xsio/forward/context.hpp"
#include "xsio/virtual/state.hpp"

namespace XSIO::Virtual {

    /// @brief Virtual Worker.
    class Worker : public $_ALLOCATOR_OBJECT(XSIO_WORKER) {
        //  TYPEDEFS  //

        /// @brief Allow the processor internal access.
        friend class Processor;

        /// @brief Allow context switching internal access.
        friend struct ::XSIO::Switch;

        //  PROPERTIES  //

        $::Atomic<bool> m_idle = false;    // Currently idle flag.
        $::Atomic<bool> m_paused = false;  // World paused flag.

        /// @brief The current worker state.
        $::Atomic<State> m_state = State::CLEANED;

        $::Atomic<Thread*> m_thread = nullptr;        // Assigned thread value.
        $::Atomic<Thread*> m_scheduler = nullptr;     // Scheduler loop thread.
        $::Atomic<Processor*> m_processor = nullptr;  // Target processor value.

        /// @brief Worker operations mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Asynchronous runtime manager.
        Async::Manager* m_manager;

        /// @brief Encapsulated thread instance.
        $::Thread::Handle m_handle;

        /// @brief Bound function-context pointer.
        Context::Pointer m_context = nullptr;

        std::condition_variable m_cv_idle;   // Idle condition.
        std::condition_variable m_cv_wake;   // Wake condition.
        std::condition_variable m_cv_state;  // State condition.

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Worker() = delete;

        /**
         * @brief Constructs a virtual worker.
         * @param manager               Runtime manager.
         * @param scheduler             Scheduler thread.
         */
        explicit Worker(Async::Manager* manager, Async::Loop* loop) :
            m_scheduler(loop->thread()), m_manager(manager), m_handle(&Worker::m_main, this) {}

        //  PUBLIC METHODS  //

        inline constexpr Context::Pointer& context() noexcept { return m_context; }
        inline constexpr const Context::Pointer& context() const noexcept { return m_context; }

        inline constexpr Thread* thread() noexcept { return m_thread; }
        inline constexpr Processor* processor() noexcept { return m_processor; }

        /// @brief Gets the current worker state.
        inline constexpr State state() const noexcept { return m_state; }

        /// @brief Denotes if the worker is no longer running.
        inline constexpr bool running() const noexcept { return m_state != State::SHUTDOWN; }

        /// @brief Pauses the worker from execution.
        void pause();

        /// @brief Resumes execution of a worker.
        void resume();

        /// @brief Forces the worker into a checkpoint state.
        void checkpoint();

        /// @brief Attempts joining the worker thread.
        inline void join() {
            for (State now = m_state; now != State::SHUTDOWN; now = m_until(now));
            m_handle.join();  // can now suitably exit the worker and join
        }

        /// @brief Attempts waking the worker.
        inline bool awaken() {
            auto lock = $::Lock::scope(m_mutex);  // lock the mutex
            bool first = m_idle.compare_exchange_strong(true, false);
            return lock.unlock(), m_cv_idle.notify_one(), first;
        }

        /**
         * @brief Handles running native-callbacks.
         * @param callback                  Native callback.
         */
        inline void native(Native&& callback) {
            m_update(State::WORKING, State::NATIVE);
            callback();  // and run the native callback
            m_update(State::NATIVE, State::WORKING);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Internal worker loop.
        void m_main();

        /// @brief Stalls the worker until needed.
        void m_stall();

        /**
         * @brief Handles processing the current work.
         * @param scheduler         Scheduler instance.
         */
        void m_process(Async::Scheduler* scheduler);

        /**
         * @brief Checks for safe states.
         * @param state             State to compare.
         */
        inline bool m_safe(State state) const noexcept {
            switch (state) {
                case State::NATIVE:
                case State::PAUSED:
                case State::WAITING:
                case State::ACQUIRE:
                case State::SHUTDOWN: return true;
                default: return false;  // heap-unsafe
            }
        }

        /**
         * @brief Waits until the current state changes.
         * @param current               State to compare against.
         */
        inline State m_until(State current) {
            auto lock = $::Lock::scope(m_mutex);  // prepare lock
            m_cv_state.wait(lock, [&] { return state() != current; });
            return lock.unlock(), m_state;  // and return the state
        }

        /**
         * @brief Updates the current worker state.
         * @param expected              Expected state.
         * @param desired               Desired state.
         */
        inline State m_update(State expected, State desired) {
            auto lock = $::Lock::scope(m_mutex);  // prepare lock
            m_state.compare_exchange_assert(expected, desired);
            return lock.unlock(), m_cv_state.notify_all(), expected;  // and set
        }
    };

}  // namespace XSIO::Virtual

#endif
