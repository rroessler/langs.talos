#ifndef _XSIO_ASYNC_MANAGER_HPP
#define _XSIO_ASYNC_MANAGER_HPP

/// XSIO Modules
#include "xsio/async/options.hpp"
#include "xsio/async/scheduler.hpp"
#include "xsio/async/shutdown.hpp"
#include "xsio/async/watchdog.hpp"
#include "xsio/signal/handler.hpp"
#include "xsio/virtual/spinner.hpp"
#include "xsio/virtual/timeout.hpp"

namespace XSIO::Async {

    /// @brief Asynchronous Runtime Manager.
    class Manager {
        //  PROPERTIES  //

        /// @brief Global manager mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Bound runtime options.
        const Options* m_options;

        /// @brief Associated watchdog instance.
        $::Ptr::Unique<Watchdog> m_watchdog = nullptr;

        /// @brief Associated scheduler instance.
        $::Ptr::Unique<Scheduler> m_scheduler = nullptr;

        /// @brief Internal shutdown handler.
        $::Ptr::Unique<Shutdown> m_shutdown = nullptr;

        /// @brief Associated signal handler.
        $::Ptr::Unique<Signal::Handler> m_signals = nullptr;

        /// @brief Readiness signaler.
        $::Signaller m_ready = $::Signaller(m_mutex);

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a manager instance.
         * @param options                   Runtime options.
         */
        explicit Manager(const Options* options = $::Global::get<Options>()) : m_options(options) {
            m_watchdog = $::New().unique<Watchdog>(this);
            m_scheduler = $::New().unique<Scheduler>(this);
            m_shutdown = $::New().unique<Shutdown>(m_mutex);
            m_signals = $::New().unique<Signal::Handler>();

            // prepare a defaulted signal handler (just-in-case)
            m_signals->bind([&](const Signal::Code&) { exit($_EXIT_FAILURE); });

            // declare as currently ready
            m_ready.notify();
        }

        //  PUBLIC METHODS  //

        inline constexpr bool running() const noexcept { return !m_shutdown->state(); }
        inline constexpr const Options* options() const noexcept { return m_options; }
        inline constexpr Scheduler* scheduler() const noexcept { return m_scheduler.get(); }
        inline constexpr Signal::Handler* signals() const noexcept { return m_signals.get(); }
        inline constexpr Shutdown* shutdown() const noexcept { return m_shutdown.get(); }

        /// @brief Blocks until the manager is ready.
        inline void ready() { m_ready.wait(); }

        /// @brief Handles launching the manager.
        inline int32_t launch() {
            // wait for exit to occur
            m_shutdown->wait();

            // join all our features
            m_scheduler->join();
            m_watchdog->join();

            // and return the necessary error-code
            return m_shutdown->code();
        }

        /**
         * @brief Handles spawning tasks.
         * @param args                      Arguments to forward.
         */
        template <std::derived_from<Task::Executor> T, class... As>
        inline T* spawn(As&&... args) {
            return m_scheduler->schedule<T>(std::forward<As>(args)...);
        }

        /**
         * @brief Handles launching the manager with an entry executor.
         * @param args                      Arguments to forward.
         */
        template <std::derived_from<Task::Executor> T, class... As>
        inline int32_t launch(As&&... args) {
            return spawn<T>(std::forward<As>(args)...), launch();
        }

        /**
         * @brief Constructs a timeout.
         * @param args                      Arguments to forward.
         */
        template <class... As>
        inline $::Ptr::Unique<Virtual::Timeout> timeout(As&&... args) {
            return $::New().unique<Virtual::Timeout>(m_scheduler.get(), std::forward<As>(args)...);
        }

        /**
         * @brief Constructs a spinner.
         * @param args                      Arguments to forward.
         */
        template <class... As>
        inline $::Spinner::Shared spinner(As&&... args) {
            auto spinner = $::New().shared<Virtual::Spinner>(std::forward<As>(args)...);
            return spinner->m_schedule(m_scheduler.get()), spinner;  // and schedule
        }

        /**
         * @brief Handles exiting the runtime.
         * @param exit_code                 Exit-code to return.
         */
        inline void exit(int32_t exit_code = $_EXIT_SUCCESS) { m_shutdown->request(exit_code); }
    };

}  // namespace XSIO::Async

#endif
