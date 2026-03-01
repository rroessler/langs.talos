#ifndef _FORGE_RUNTIME_EXECUTOR_HPP
#define _FORGE_RUNTIME_EXECUTOR_HPP

/// Forge Modules
#include "forge/runtime/isolate.hpp"

namespace Forge::Runtime {

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

}  // namespace Forge::Runtime

#endif
