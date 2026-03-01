#ifndef _SHELL_APPLICATION_COMMAND_HPP
#define _SHELL_APPLICATION_COMMAND_HPP

/// Vendor Modules
#include <talos/talos.hpp>

/// Shell Modules
#include "shell/forward/application.hpp"
#include "shell/validators/duration.hpp"
#include "xtdlib/string/convert.hpp"

//  X-MACROS  //

/// @brief Common Command Options.
#define SHELL_XX_OPTIONS_COMMON(X) X("-h, --help", "Display this command help menu")

/// @brief Common Bundle Options.
#define SHELL_XX_OPTIONS_BUNDLE(X)                     \
    X("--env", "Set environment file to inherit")      \
    X("--lint", "Force extra linting to occur")        \
    X("--hints", "Allows showing extra linting hints") \
    X("", "")                                          \
    X("--optless", "Disables all runtime optimization techniques")

/// @brief Common Launch Options.
#define SHELL_XX_OPTIONS_LAUNCH(X) \
    SHELL_XX_OPTIONS_BUNDLE(X)     \
    X("--jitless", "Disables runtime allocation of executable memory")

//  NAMESPACES  //

namespace Shell::Command {

    /// @brief Command Usage Abstraction.
    struct $_ABSTRACT Usage {
        //  CONSTRUCTORS  //

        /// @brief Default destructor.
        virtual ~Usage() = default;

        //  PUBLIC METHODS  //

        /// @brief Handles getting help details.
        inline $::String::Buffer help() const {
            $::String::Stream oss = {};  // build the stream
            if ($::Dye::enabled()) $::Dye::enabled(oss, true);
            return m_help(oss), oss.str();  // and construct now
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles showing usage details.
         * @param os                        Output stream.
         */
        virtual void m_help($::Stream::Output& os) const = 0;
    };

    /// @brief Handles describing usage details.
    class Descriptor : public Usage {
        //  TYPEDEFS  //

        /// @brief Core list entry value.
        using Entry = std::pair<$::ANSI, $::String::View>;

        /// @brief Denotes a positional item.
        using Positional = std::pair<$::String::View, bool>;

        /// @brief Underlying descriptor list details.
        using List = std::vector<Entry>;

        /// @brief Initializer list value.
        using Initializer = std::initializer_list<Entry>;

        //  PROPERTIES  //

        /// @brief Explicit descriptor title.
        $::String::View m_title;

        List m_commands = {};     // Sub-commands available.
        List m_options = {};      // Explicit options available.
        List m_environment = {};  // Environment flags available.

        /// @brief Available positionals.
        std::vector<Positional> m_positionals = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a descriptor instance.
         * @param title                     Title to bind.
         */
        explicit Descriptor(const $::String::View& title = "") : m_title(title) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying title value.
        inline constexpr $::String::View title() const { return m_title; }

        inline Descriptor& commands(const Initializer& list) { return m_commands = list, *this; }
        inline Descriptor& options(const Initializer& list) { return m_options = list, *this; }
        inline Descriptor& environment(const Initializer& list) { return m_environment = list, *this; }
        inline Descriptor& positionals(const std::initializer_list<Positional>& list) {
            return m_positionals = list, *this;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles showing usage details.
         * @param os                        Output stream.
         */
        void m_help($::Stream::Output& os) const final;

        /**
         * @brief Handles printing positional arguments.
         * @param os                        Output stream.
         * @param entry                     Positional entry.
         */
        void m_help($::Stream::Output& os, const Positional& entry) const;

        /**
         * @brief Handles showing details for a desired list.
         * @param os                        Output stream.
         * @param title                     Title to use.
         * @param list                      List of details.
         */
        void m_help($::Stream::Output& os, const $::String::View& title, const List& list) const;

        /**
         * @brief Gets the padding associated with a list.
         * @param list                      List to get padding of.
         */
        inline size_t m_padding(const List& list) const {
            // prepare some variables to define our padding now
            static constexpr size_t alignment = 8;

            // prepare our maximum to now be used
            auto maximum = m_maximum(list) + alignment / 2;

            // and construct the maximum padding to be used
            return maximum + alignment - maximum % alignment;
        }

        /**
         * @brief Handles comparing to entries.
         * @param a                         Entry alpha.
         * @param b                         Entry beta.
         */
        static bool m_compare(const Entry& a, const Entry& b) {
            return a.first.value().size() < b.first.value().size();
        }

        /**
         * @brief Gets a lists maximum entry.
         * @param list                      List to maximize.
         */
        static size_t m_maximum(const List& list) {
            return list.empty() ? 0 : std::max_element(list.cbegin(), list.cend(), m_compare)->first.value().size();
        }
    };

    /// @brief Command Abstraction.
    class $_ABSTRACT Abstract : public Usage {
        //  TYPEDEFS  //

        /// @brief Allow programs internal access.
        friend class ::Shell::Program;

       protected:
        //  PROPERTIES  //

        /// @brief Associated descriptor value.
        Descriptor m_descriptor;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Abstract() = delete;

        /**
         * @brief Constructs a command instance.
         * @param name                  Name of command.
         */
        explicit Abstract(const $::String::View& name) : m_descriptor(name) {}

        /// @brief Abstract destructor.
        virtual ~Abstract() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the command name.
        inline constexpr $::String::View name() const { return m_descriptor.title(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles subscribing a command instance.
         * @param command                   Command to be subscribed.
         * @param options                   Options instance to bind.
         */
        virtual void m_subscribe(CLI::App* command) = 0;

        /**
         * @brief Handles emplacing common options.
         * @param command                   Command to update.
         * @param options                   Runtime options.
         * @param runtime                   Flag for extra.
         */
        void m_common(CLI::App* command, Talos::Runtime::Options* options, bool runtime);

        /**
         * @brief Handles throwing immediate failures.
         * @param message                   Failure message.
         * @param args                      Message arguments.
         */
        template <class... As>
        $_NORETURN inline void m_fail(fmt::format_string<As...> message, As&&... args) const {
            auto title = $::Convert::capitalize(name());
            $::IO::cerr() << $::Dye::red("Exception.{0}", title).bold() << ": ";
            $::IO::cerr() << fmt::format(message, std::forward<As>(args)...) << '\n';
            throw CLI::RuntimeError($_EXIT_FAILURE);  // and declare a failure
        }

        /**
         * @brief Handles showing immediate warnings.
         * @param message                   Warning message.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline void m_warn(fmt::format_string<As...> message, As&&... args) const {
            auto title = $::Convert::capitalize(name());  // prepare the name
            $::IO::cerr() << $::Dye::yellow("Warning.{0}", title).bold() << ": ";
            $::IO::cerr() << fmt::format(message, std::forward<As>(args)...) << '\n';
        }

        /**
         * @brief Handles showing immediate warnings.
         * @param verbose                   Verbosity flag.
         * @param message                   Warning message.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline void m_warn(bool verbose, fmt::format_string<As...> message, As&&... args) const {
            if (verbose) m_warn(message, std::forward<As>(args)...);  // allowed to print
        }

        /**
         * @brief Handles emitting help information.
         * @param os                        Output stream.
         */
        inline void m_help($::Stream::Output& os) const final { os << m_descriptor.help(); }
    };

}  // namespace Shell::Command

#endif
