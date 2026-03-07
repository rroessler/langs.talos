#ifndef _TALOS_RELINT_CONTEXT_HPP
#define _TALOS_RELINT_CONTEXT_HPP

/// Talos Modules
#include "talos/diagnostic/reporter.hpp"
#include "talos/relint/hooks.hpp"
#include "talos/relint/metadata.hpp"
#include "talos/relint/rule.hpp"
#include "talos/relint/service.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Relint {

    /// @brief Limited Rule Context Handler.
    class $_ABSTRACT Context {
        //  TYPEDEFS  //

        /// @brief Allow the analyzer internal access.
        friend struct Analyzer;

        //  PROPERTIES  //

        /// @brief Services container.
        XI::Container* m_services = nullptr;

        /// @brief The currently available linting hooks/rules.
        $::Ptr::Unique<Hooks> m_hooks = nullptr;

        /// @brief Underlying diagnostics reporter.
        Diagnostic::Reporter* m_reporter = nullptr;

        /// @brief Current metadata value.
        $::Ptr::Unique<Metadata> m_mirrors = nullptr;

        /// @brief Currently deferred values.
        std::vector<Deferrer> m_deferred = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted context.
        explicit Context();
        explicit Context(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief The associate resource for the context.
        inline constexpr $::URI::View resource() const noexcept {
            return m_reporter ? m_reporter->resource() : $::URI::Anonymous();
        }

        /// @brief Available metadata mirrors.
        inline constexpr const Metadata* mirrors() const noexcept { return m_mirrors.get(); }

        /**
         * @brief Reports a diagnostic.
         * @param location                  Resource location.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr void report(const Resource::Location& location, As&&... args) {
            auto stack = location.anonymous() ? Resource::Stack() : Resource::Stack({ location });
            m_report(stack, std::forward<As>(args)...);  // request from underlying
        }

        /**
         * @brief Reports a diagnostic.
         * @param location                  Resource location.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr void report(const Syntax::Bounds& location, As&&... args) {
            report(Resource::Location(location.resource(), location.bounds()), std::forward<As>(args)...);
        }

        /**
         * @brief Reports a diagnostic.
         * @param node                      Syntax node.
         * @param args                      Message arguments.
         */
        template <std::derived_from<Syntax::Node> T, class... As>
        inline constexpr void report(const T* node, As&&... args) {
            report(node->traits()->location(), std::forward<As>(args)...);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Constructs a context instance.
         * @param tree                      Syntax tree node.
         * @param reporter                  Reporter to bind.
         */
        inline constexpr auto m_context(const Syntax::Tree* tree, Diagnostic::Reporter* reporter) {
            // update the current reporter reference
            m_reporter = reporter;

            // construct all the rules to be used now
            m_hooks = m_services->get<Service>()->hooks(tree->resource());

            // and allow destruction of the contextual items now
            return $::Functor::Defer([&] { m_hooks = nullptr, m_reporter = nullptr; });
        }

        /**
         * @brief Classifies a rule into a desired diagnostic.
         * @param rule                      Rule to classify.
         */
        inline constexpr Diagnostic::Code m_classify(const Rule* rule) const noexcept {
            auto identifier = rule->documentation.identifier;
            const auto& rules = m_hooks->options()->rules;

            auto iter = rules.find(identifier);  // get the potential severity iterator now
            auto severity = iter == rules.end() ? rule->severity : rules.at(identifier);

            // get the deprecated mask to be used as well
            auto deprecated = rule->deprecated ? 1 << 4 : 0;

            // prepare the necessary code now
            return 10000000 | (1 << static_cast<uint8_t>(severity)) | deprecated;
        }

        /**
         * @brief Formats linter messages.
         * @param rule                      Linter rule.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr $::String::Buffer m_format(const Rule* rule, As&&... args) const noexcept {
            return fmt::format(fmt::runtime(rule->documentation.message), std::forward<As>(args)...);
        }

        /**
         * @brief Reports linter errors.
         * @param stack                     Resource stack.
         * @param rule                      Linter rule.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr void m_report(const Resource::Stack& stack, const Rule* rule, As&&... args) {
            // ignore if there is no suitable reporter at all
            if (m_reporter == nullptr) return;

            // get the associated code for the rule
            auto code = m_classify(rule);

            // format the message to be used
            auto message = m_format(rule, std::forward<As>(args)...);

            // and finally construct the resulting diagnostic
            m_reporter->emit(stack, code, message);
        }

        /**
         * @brief Reports a diagnostic.
         * @param stack                     Resource stack.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr void m_report(const Resource::Stack& stack, Diagnostic::Code code, As&&... args) {
            if (m_reporter) m_reporter->emit(stack, code, std::forward<As>(args)...);
        }
    };

}  // namespace Talos::Relint

#endif
