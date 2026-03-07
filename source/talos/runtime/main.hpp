#ifndef _TALOS_RUNTIME_MAIN_HPP
#define _TALOS_RUNTIME_MAIN_HPP

/// Talos Modules
#include "talos/async/main.hpp"

namespace Talos::Runtime {

    /// @brief Runtime Main Thread.
    struct Main : public Async::Main {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Async::Main::Main;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles launching the runtime.
        $_NORETURN void m_execute() final;

        /**
         * @brief Handles analyzing a resource.
         * @param resource              Resource to analyze.
         */
        void m_analyze(const $::URI::Buffer& resource);

        /**
         * @brief Handles importing a script.
         * @param script                Script to import.
         */
        Value::Any m_import(const $::String::View& script);
    };

}  // namespace Talos::Runtime

#endif
