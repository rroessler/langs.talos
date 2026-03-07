#ifndef _TALOS_ASYNC_MAIN_HPP
#define _TALOS_ASYNC_MAIN_HPP

/// Talos Modules
#include "talos/async/service.hpp"
#include "talos/runtime/executor.hpp"

namespace Talos::Async {

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

}  // namespace Talos::Async

#endif
