#ifndef _TALOS_DIAGNOSTIC_VIEW_HPP
#define _TALOS_DIAGNOSTIC_VIEW_HPP

/// Talos Includes
#include "talos/diagnostic/traits.hpp"
#include "talos/resource/location.hpp"

namespace Talos::Diagnostic {

    /// @brief Compact Diagnostic View.
    class View : public $::Printable {
        //  TYPEDEFS  //

        /// @brief Allow the reporter internal access.
        friend class Reporter;

        //  PROPERTIES  //

        /// @brief Diagnostic code.
        Code m_code = -1;

        /// @brief Stacktrace for a diagnostic.
        Resource::Stack m_stack = {};

        /// @brief Bound message value.
        $::String::Buffer m_message = "...";

        /// @brief Bound severity value.
        Severity m_severity = Severity::ERROR;

       private:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted message.
        constexpr View() = default;

       public:
        //  OPERATOR METHODS  //

        /// @brief Checks if diagnostics are equal.
        inline constexpr auto operator==(const View& other) const {
            if (std::tie(m_code, m_message) != std::tie(other.m_code, other.m_message)) return false;
            return (m_stack.empty() && other.m_stack.empty()) || m_stack.front() == other.m_stack.front();
        }

        //  PUBLIC METHODS  //

        inline constexpr Code code() const noexcept { return m_code; }
        inline constexpr Severity severity() const noexcept { return m_severity; }
        inline constexpr $::String::View message() const noexcept { return m_message; }
        inline constexpr const Resource::Stack& stack() const noexcept { return m_stack; }

        inline constexpr Tags tags() const noexcept { return Traits::tags(m_code); }
        inline constexpr $::String::View category() const noexcept { return Traits::category(m_code); }

        /// @brief Converts a diagnostic to its underlying LSP equivalent.
        inline constexpr XLSP::Diagnostic underlying() const noexcept {
            // prepare the baseline underlying diagnostic to be constructed
            auto diagnostic = XLSP::Diagnostic();

            // update each item as necessary
            diagnostic.code = m_code;
            diagnostic.source = "TAL";
            diagnostic.message = m_message;

            diagnostic.tags = tags();
            diagnostic.severity = severity();

            // update all the conditional items required
            if (auto range = m_range()) diagnostic.range = *range;

            // and return the resulting diagnostic
            return diagnostic;
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles resolving an output range.
        inline constexpr std::optional<XLSP::Range> m_range() const noexcept {
            // ignore if not suitable range value
            if (m_stack.empty()) return std::nullopt;

            // get the top-most range value
            auto range = m_stack.back().range();
            auto start = range.start, end = range.end;

            // re-construct with correct positions now
            return XLSP::Range(start.line - 1, start.column - 1, end.line - 1, end.column - 1);
        }

        /**
         * @brief Handles printing a diagnostic.
         * @param os                        Output stream.
         * @param self                      Diagnostic view.
         */
        static void m_print($::Stream::Output& os, const View& self);
    };

}  // namespace Talos::Diagnostic

#endif
