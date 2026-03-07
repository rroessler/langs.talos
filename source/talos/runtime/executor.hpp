#ifndef _TALOS_RUNTIME_EXECUTOR_HPP
#define _TALOS_RUNTIME_EXECUTOR_HPP

/// Talos Modules
#include "talos/runtime/isolate.hpp"

namespace Talos::Runtime {

    /// @brief Isolate Executor Abstraction.
    struct $_ABSTRACT Executor : public Async::Task<Executor>, public Isolate {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an isolate executor.
         * @param args                  Arguments to bind.
         */
        template <class... As>
        explicit Executor(As&&... args) : Isolate(std::forward<As>(args)...) {}

        //  PUBLIC METHODS  //

        /// @brief Allow getting the underlying thread instance.
        inline constexpr Async::Thread* thread() const noexcept final { return Async::Task<Executor>::thread(); }
    };

}  // namespace Talos::Runtime

#endif
