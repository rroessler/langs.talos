#ifndef _SHELL_LAUNCH_ACTION_HPP
#define _SHELL_LAUNCH_ACTION_HPP

/// Shell Modules
#include "shell/application/command.hpp"

namespace Shell::Launch {

    /// @brief Launch Options.
    using Options = Talos::Runtime::Options;

    /// @brief Launch Command.
    class Action : public Command::Abstract {
        //  PROPERTIES  //

        /// @brief Underlying runtime options.
        Options m_options = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a launch action.
        explicit Action();

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the launcher.
        void m_execute();

        /**
         * @brief Handles subscribing the "run" command.
         * @param command                   CLI application.
         */
        void m_subscribe(CLI::App* command) final;
    };

}  // namespace Shell::Launch

#endif
