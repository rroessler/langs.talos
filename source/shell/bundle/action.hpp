#ifndef _SHELL_BUNDLE_ACTION_HPP
#define _SHELL_BUNDLE_ACTION_HPP

/// Vendor Modules
/// Shell Modules
#include "shell/application/command.hpp"

namespace Shell::Bundle {

    /// @brief Launch Options.
    using Options = Talos::Bundle::Options;
    using Runtime = Talos::Runtime::Options;

    /// @brief Bundle Command.
    class Action : public Command::Abstract {
        //  PROPERTIES  //

        /// @brief Underlying bundler options.
        Options m_options = {};

        /// @brief Underlying runtime options.
        Runtime m_runtime = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a bundle action.
        explicit Action();

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the bundler.
        void m_execute();

        /**
         * @brief Handles subscribing the "bundle" command.
         * @param command                   CLI application.
         */
        void m_subscribe(CLI::App* command) final;
    };

}  // namespace Shell::Bundle

#endif
