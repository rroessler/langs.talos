#ifndef _XSIO_CONTEXT_SWITCH_HPP
#define _XSIO_CONTEXT_SWITCH_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/forward/context.hpp"

namespace XSIO {

    /// @brief Context Switches.
    struct Switch : public $::Never {
        //  PUBLIC METHODS  //

        /**
         * @brief Waits for a thread callback.
         * @param thread                    Thread to await.
         * @param processor                 Virtual processor.
         */
        static void wait_for_thread(Virtual::Thread* thread, Virtual::Processor* processor);

        /**
         * @brief Waits for the scheduler to acquire a worker.
         * @param loop                      Scheduler loop to wait.
         */
        static void wait_for_scheduler(Async::Loop* loop);

        /**
         * @brief Yields a worker to the scheduler.
         * @param worker                    Worker to yield.
         */
        static void yield_to_worker(Virtual::Worker* worker);

        /**
         * @brief Yields the scheduler to an acquired thread.
         * @param loop                      Scheduler loop to yield.
         * @param thread                    Thread to initialize.
         */
        static void yield_to_thread(Async::Loop* loop, Virtual::Thread* thread);

        /**
         * @brief Yields a thread to the scheduler.
         * @param thread                    Thread to yield.
         * @param state                     Next thread state.
         * @param callback                  Optional callback.
         */
        static void yield_to_scheduler(Virtual::Thread* thread, Virtual::State state);
        static void yield_to_scheduler(Virtual::Thread* thread, Virtual::State state, Context::Callback&& callback);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles a context transfer.
         * @param transfer                  Transfer to occur.
         */
        $_NORETURN static void m_transfer(Context::Transfer transfer);

        /**
         * @brief Handles allocating a thread-stack.
         * @param thread                    Thread to acquire onto.
         * @param worker                    Worker instance to bind.
         */
        static void m_allocate(Virtual::Thread* thread, Virtual::Worker* worker);
    };

}  // namespace XSIO

#endif
