#ifndef _SHELL_APPLICATION_PROGRAM_HPP
#define _SHELL_APPLICATION_PROGRAM_HPP

/// Vendor Modules
#include <CLI/CLI.hpp>

/// Shell Modules
#include "shell/application/command.hpp"

namespace Shell {

    /// @brief Core Application Instance.
    class Program : public Command::Usage {
        //  TYPEDEFS  //

        /// @brief Formatter Implementation.
        class Formatter : public CLI::FormatterBase {
            //  PROPERTIES  //

            /// @brief Attached program instance.
            Program* m_program;

           public:
            //  CONSTRUCTORS  //

            /**
             * @brief Constructs a formatter instance.
             * @param program               Program instance.
             */
            explicit Formatter(Program* program) : m_program(program) {}

            //  PUBLIC METHODS  //

            /**
             * @brief Handles constructing help outputs.
             * @param app                   CLI application.
             * @param name                  Name of command.
             * @param mode                  Output mode.
             */
            $::String::Buffer make_help(
                const CLI::App* app, $::String::Buffer name, CLI::AppFormatMode mode) const final;
        };

        //  PROPERTIES  //

        /// @brief Underlying application instance.
        $::Ptr::Unique<CLI::App> m_app;

        /// @brief Subscribed commands available.
        $::Record<$::Ptr::Unique<Command::Abstract>> m_commands = {};

       public:
        //  CONSTRUCTORS  //

        /** Constructs a program instance. */
        explicit Program();

        //  PUBLIC METHODS  //

        /**
         * @brief Handles launching the program.
         * @param argc                      Argument count.
         * @param argv                      Variadic arguments.
         */
        int32_t launch(int32_t argc, char** argv);

        /// @brief Handles registering program commands.
        template <std::derived_from<Command::Abstract> T>
        inline T* subscribe() {
            // prepare the underlying action instance
            auto action = $::New().unique<T>();
            auto* reference = action.get();
            auto name = action->name();

            // prepare the subcommand that is available to be used
            auto* command = m_app->add_subcommand($::String::Buffer(name));
            command->callback([name] { $_ABORT("Action '{0}' not yet implemented", name); });
            reinterpret_cast<Command::Abstract*>(reference)->m_subscribe(command);

            // empplace the comand as necessary now onto the list
            return m_commands.emplace(name, std::move(action)), reference;
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles showing the available vendors.
        static void m_vendors();

        /// @brief Handles showing the revision details.
        static void m_revision();

        /**
         * @brief Handles printing program usage.
         * @param os                        Output stream.
         */
        void m_help($::Stream::Output& os) const final;

        /**
         * @brief Handles setting the logger level.
         * @param level                     Level to bind.
         */
        static void m_level(const $::String::View& level);

        /**
         * @brief Handles setting the necessary color-mode.
         * @param color                     Color to bind.
         */
        static void m_color(const $::String::View& color);

        /**
         * @brief Handles setting the necessary progress mode.
         * @param spinners                  Spinners to bind.
         */
        static void m_progress(const $::String::View& spinners);
    };

}  // namespace Shell

#endif
