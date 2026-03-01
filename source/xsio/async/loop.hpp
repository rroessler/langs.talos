#ifndef _XSIO_ASYNC_LOOP_HPP
#define _XSIO_ASYNC_LOOP_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/task/executor.hpp"

namespace XSIO::Async {

    /// @brief Scheduler Loop Task.
    class Loop : public Task::Abstract<Loop> {
        //  PROPERTIES  //

        /// @brief Asynchronous runtime manager.
        Manager* m_manager;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a loop instance.
         * @param manager               Runtime manager.
         */
        explicit Loop(Manager* manager) : m_manager(manager) {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles the scheduling loop.
        $_NORETURN void m_execute() final;

        /**
         * @brief Handles when acquisitions fail.
         * @param processor             Processor to stall.
         */
        void m_busy(Virtual::Processor* processor);

        /**
         * @brief Handles incoming threads.
         * @param thread                Thread to fulfill.
         */
        void m_acquired(Virtual::Thread* thread, Virtual::Processor* processor);
    };

}  // namespace XSIO::Async

#endif
