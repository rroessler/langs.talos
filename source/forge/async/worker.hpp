#ifndef _FORGE_ASYNC_WORKER_HPP
#define _FORGE_ASYNC_WORKER_HPP

/// Forge Modules
#include "forge/async/future.hpp"
#include "forge/resource/frame.hpp"
#include "forge/runtime/executor.hpp"

namespace Forge::Async {

    /// @brief Future Worker Isolate.
    class Worker : public Runtime::Executor {
        //  PROPERTIES  //

        /// @brief Underlying resource frame (for backtraces)
        $::Ptr::Unique<Resource::Frame> m_caller = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a future isolate.
         * @param services          Services container.
         * @param future            Future to bind.
         * @param trace             Resource trace.
         */
        explicit Worker(XI::Container* services, const Future& future) : Executor(services, future) {}
        explicit Worker(XI::Container* services, const Future& future, const Resource::Trace& trace) :
            Worker(services, future) {
            if (!trace.anonymous()) m_caller = $::New().unique<Resource::Frame>(this, trace);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles launching the runtime.
        void m_execute() final;
    };

}  // namespace Forge::Async

#endif
