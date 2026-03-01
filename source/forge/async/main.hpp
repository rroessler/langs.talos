#ifndef _FORGE_ASYNC_MAIN_HPP
#define _FORGE_ASYNC_MAIN_HPP

/// Forge Modules
#include "forge/async/service.hpp"
#include "forge/runtime/executor.hpp"

namespace Forge::Async {

    /// @brief Describes a main-entry isolate.
    struct $_ABSTRACT Main : public Runtime::Executor {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a main-isolate.
         * @param args              Executor arguments.
         */
        template <class... As>
        explicit Main(As&&... args) : Executor(std::forward<As>(args)...) {
            service<Service>()->m_main = this;
        }
    };

}  // namespace Forge::Async

#endif
