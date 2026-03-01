#ifndef _XSIO_ASYNC_SCHEDULER_HPP
#define _XSIO_ASYNC_SCHEDULER_HPP

/// XSIO Modules
#include "xsio/async/storage.hpp"
#include "xsio/memory/stack.hpp"
#include "xsio/virtual/processor.hpp"
#include "xsio/virtual/thread.hpp"
#include "xsio/virtual/worker.hpp"

//  X-MACROS  //

/// @brief Available scheduler targets.
#define XX_SCHEDULER_TARGETS(X) \
    X(Memory::Stack)            \
    X(Virtual::Thread)          \
    X(Virtual::Processor)

//  NAMESPACES  //

namespace XSIO::Async {

    /// @brief Event Loop Scheduler.
    class Scheduler {
        //  PROPERTIES  //

        /// @brief Underlying manager instance.
        Async::Manager* m_manager;

        /// @brief Runtime storage.
        $::Ptr::Unique<Storage> m_storage;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Scheduler() = delete;

        /**
         * @brief Constructs a scheduler instance.
         * @param manager                   Asynchronous manager.
         */
        explicit Scheduler(Manager* manager);

        //  PUBLIC METHODS  //

        inline constexpr Task::Queue* tasks() const noexcept { return m_storage->tasks.get(); }
        inline constexpr const auto& threads() const noexcept { return m_storage->instances.threads; }
        inline constexpr const auto& workers() const noexcept { return m_storage->instances.workers; }
        inline constexpr const auto& processors() const noexcept { return m_storage->instances.processors; }

        /// @brief Gets the total task-queue size.
        inline constexpr size_t pending() const noexcept {
            auto predicate = [](size_t acc, const auto& processor) { return acc + processor->pending(); };
            return std::ranges::fold_left(processors(), m_storage->tasks->size(), predicate);
        }

        /// @brief Joins all scheduler workers.
        inline void join() {
            for (const auto& worker : workers()) worker->awaken();  // first awaken, then join
            for (const auto& worker : workers()) worker->join(), $_EXPECT(!worker->running());
        }

        /// @brief Pauses execution of all the available workers.
        inline constexpr auto pause() {
            for (const auto& worker : workers()) worker->pause();
            return $::Functor::Defer([&] { resume(); });  // resume
        }

        /// @brief Resumes execution of all workers.
        inline constexpr void resume() {
            for (const auto& worker : workers()) worker->resume();
        }

        /// @brief Handles acquiring various items.
        template <class T>
        T* acquire();

        /**
         * @brief Handles releasing various values.
         * @param value                     Value to recycle.
         */
        template <class T>
        void recycle(T* value);

        /**
         * @brief Handles assigning a processor to a worker.
         * @param worker                    Worker to assign to.
         */
        bool assign(Virtual::Worker* worker);

        /**
         * @brief Handles releasing a processor from a worker.
         * @param worker                    Worker to release from.
         */
        void release(Virtual::Worker* worker);

        /**
         * @brief Attempts stealing threads from another processor.
         * @param target                    Target to steal from.
         */
        inline bool steal(Virtual::Processor* target) {
            // attempt stealing from other processor now
            for (const auto& processor : processors()) {
                if (processor.get() == target) continue;
                if (processor->balance(target)) return true;
            }

            // failed to balance any processors
            return false;
        }

        /**
         * @brief Handles scheduling a thread for execution.
         * @param thread                    Thread to schedule.
         * @param processor                 Optional processor.
         */
        inline void schedule(Virtual::Thread* thread, Virtual::Processor* processor = nullptr) {
            // ensure the thread is actually ready for running
            $_ASSERT(thread->state() == Virtual::State::READY);

            // if we can push onto a processor, then do so
            if (processor) return processor->schedule(thread);

            // attempt pushing the thread onto the global task-queue
            m_storage->tasks->schedule(thread), m_awaken();
        }

        /**
         * @brief Handles scheduling an executor.
         * @param args                      Arguments to bind.
         */
        template <std::derived_from<Task::Executor> T, class... As>
        inline T* schedule(As&&... args) {
            Virtual::Processor* processor = nullptr;  // global task
            return schedule<T>(processor, std::forward<As>(args)...);
        }

        /**
         * @brief Handles scheduling an executor.
         * @param processor                 Processor to bind.
         * @param args                      Arguments to bind.
         */
        template <std::derived_from<Task::Executor> T, class... As>
        inline T* schedule(Virtual::Processor* processor, As&&... args) {
            auto* thread = acquire<Virtual::Thread>();  // force acquire
            auto* task = thread->assign<T>(std::forward<As>(args)...);
            return thread->awaken(), schedule(thread, processor), task;
        }

       private:
        //  PRIVATE METHODS  //

        /** Attempts trying to awaken a worker instance. */
        inline void m_awaken() {
            for (const auto& worker : workers()) {
                if (worker->state() != Virtual::State::WAITING) continue;
                if (worker->awaken()) return;  // successfully awoken one
            }
        }
    };

}  // namespace XSIO::Async

//  SPECIALIZATIONS  //

#define X(T, ...)                               \
    template <>                                 \
    XSIO::T* XSIO::Async::Scheduler::acquire(); \
                                                \
    template <>                                 \
    void XSIO::Async::Scheduler::recycle(T*);

XX_SCHEDULER_TARGETS(X)
#undef X

//  UNDEFINES  //

#undef XX_SCHEDULER_TARGETS

#endif
