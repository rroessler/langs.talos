#ifndef _SHELL_LINT_ACTION_HPP
#define _SHELL_LINT_ACTION_HPP

/// Shell Modules
#include "shell/application/command.hpp"

namespace Shell::Lint {

    /// @brief Linting Options.
    using Options = Talos::Runtime::Options;

    /// @brief Lint Command.
    class Action : public Command::Abstract {
        //  PROPERTIES  //

        /// @brief Underlying server options.
        Options m_options = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a lint action.
        explicit Action();

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the linter.
        void m_execute() const;

        /**
         * @brief Handles subscribing the "lint" command.
         * @param command                   CLI application.
         */
        void m_subscribe(CLI::App* command) final;
    };

}  // namespace Shell::Lint

#endif
