#ifndef _XSIO_VIRTUAL_SPINNER_HPP
#define _XSIO_VIRTUAL_SPINNER_HPP

/// XSIO Modules
#include "xsio/async/scheduler.hpp"
#include "xsio/task/executor.hpp"
#include "xsio/virtual/thread.hpp"

namespace XSIO::Virtual {

    /// @brief Constructs a virtualized spinner.
    class Spinner : public $::Spinner::Abstract {
        //  TYPEDEFS  //

        /// @brief Allow the manager internal access.
        friend class Async::Manager;

        /// @brief Spinner Worker Thread.
        class Worker : public Task::Abstract<Worker> {
            //  PROPERTIES  //

            /// @brief The bound spinner instance.
            $::Ptr::Shared<Spinner> m_self;

           public:
            //  CONSTRUCTORS  //

            /**
             * @brief Constructs a worker instance.
             * @param self              Spinner value.
             */
            explicit Worker(const $::Ptr::Shared<Spinner>& self) : m_self(self) {}

           protected:
            //  PRIVATE METHODS  //

            /// @brief Handles executing the spinner.
            inline void m_execute() final { m_self->m_writer(); }
        };

        //  PROPERTIES  //

        /// @brief Internal spinner worker.
        Worker* m_worker = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the baseline spinner instance.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles running the sleep instance.
        inline void m_sleep() const noexcept final { m_worker->thread()->sleep(options().tick); }

        /**
         * @brief Starts scheduling the spinner instance.
         * @param scheduler             Asynchronous scheduler.
         */
        inline void m_schedule(Async::Scheduler* scheduler) { m_worker = scheduler->schedule<Worker>(m_as<Spinner>()); }
    };

}  // namespace XSIO::Virtual

#endif
