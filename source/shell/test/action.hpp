#ifndef _SHELL_TEST_ACTION_HPP
#define _SHELL_TEST_ACTION_HPP

/// Shell Modules
#include "shell/application/command.hpp"

namespace Shell::Test {

    /// @brief Testing Options.
    using Options = Talos::Runtime::Options;

    /// @brief Test Command.
    class Action : public Command::Abstract {
        //  PROPERTIES  //

        /// @brief Underlying runtime options.
        Options m_options = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a test action.
        explicit Action();

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the testr.
        void m_execute() const;

        /**
         * @brief Handles subscribing the "test" command.
         * @param command                   CLI application.
         */
        void m_subscribe(CLI::App* command) final;
    };

}  // namespace Shell::Test

#endif
