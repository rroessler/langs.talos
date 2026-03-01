#ifndef _SHELL_TASK_ACTION_HPP
#define _SHELL_TASK_ACTION_HPP

/// Shell Modules
#include "shell/task/branch.hpp"

namespace Shell::Task {

    /// @brief Task Command.
    struct Action : public Command::Abstract {
        //  CONSTRUCTORS  //

        /// @brief Constructs a task action.
        explicit Action();

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles executing the task.
         * @param command                   Sub-command.
         */
        void m_execute(CLI::App* command) const;

        /**
         * @brief Handles delegating a branch.
         * @param branch                    Branch to run.
         * @param workspace                 Workspace to use.
         */
        void m_delegate(const Branch& branch) const;

        /**
         * @brief Handles subscribing the "task" command.
         * @param command                   CLI application.
         */
        void m_subscribe(CLI::App* command) final;

        /**
         * @brief Resolves branches from arguments.
         * @param state                     Global branch state.
         * @param argv                      Arguments to resolve.
         */
        void m_branch(Branch& state, Collection& argv) const;
    };

}  // namespace Shell::Task

#endif
