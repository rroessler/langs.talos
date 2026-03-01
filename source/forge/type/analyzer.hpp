#ifndef _FORGE_TYPE_ANALYZER_HPP
#define _FORGE_TYPE_ANALYZER_HPP

/// Forge Modules
#include "forge/shape/service.hpp"
#include "forge/syntax/node.hpp"
#include "forge/type/context.hpp"
#include "forge/type/deduction.hpp"
#include "forge/type/options.hpp"
#include "forge/type/world.hpp"

/// Syntax Modules
#include "forge/syntax/annotation/generics.hpp"
#include "forge/syntax/declaration/variable.hpp"

/// Type Modules
#include "forge/type/utility/intrinsics.hpp"

namespace Forge::Type {

    /// @brief Transient Type Checker.
    class Analyzer : public XI::Define<Analyzer, XI::Unique> {
        //  TYPEDEFS  //

        /// @brief Allow world-scopes internal access.
        friend class Scope;

        //  PROPERTIES  //

        /// @brief Services container.
        XI::Container* m_services;

        /// @brief Current scoped world instance.
        World* m_world = nullptr;

        /// @brief The underlying global type-world.
        World* m_globals = nullptr;

        /// @brief Underlying diagnostics reporter.
        Diagnostic::Reporter* m_reporter = nullptr;

        /// @brief Current context value.
        $::Ptr::Unique<Context> m_context = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an analyzer instance.
         * @param services                  Services container.
         */
        explicit Analyzer();
        explicit Analyzer(XI::Container* services);

        //  PUBLIC METHODS  //

        inline constexpr Context* context() const noexcept { return m_context.get(); }
        inline constexpr Exports& exports() const noexcept { return m_context->exports(); }
        inline constexpr Variable::Captures& captures() const noexcept { return m_context->captures(); }
        inline constexpr Shape::Service* shapes() const noexcept { return m_services->get<Shape::Service>(); }

        inline constexpr Depth depth() const noexcept { return m_world->depth(); }
        inline constexpr $::URI::View resource() const noexcept {
            return m_reporter ? m_reporter->resource() : $::URI::Anonymous();
        }

        inline constexpr World* world() noexcept { return m_world; }
        inline constexpr const World* world() const noexcept { return m_world; }
        inline constexpr const World* globals() const noexcept { return m_world; }
        inline constexpr $::Ptr::Unique<Scope> scope() noexcept { return $::New().unique<Scope>(this); }

        /**
         * @brief Handles tracing reporter resources.
         * @param node                      Node to trace.
         */
        inline constexpr Diagnostic::Scope trace(const Syntax::Node* node) {
            return node ? trace(node->traits()->location()) : Diagnostic::Scope();
        }

        /**
         * @brief Handles tracing reporter resources.
         * @param location                  Location to trace.
         */
        inline constexpr Diagnostic::Scope trace(const Resource::Location& location) {
            return Diagnostic::Scope(m_reporter, location);
        }

        /**
         * @brief Handles deferring type-checking.
         * @param deduction                 Passthrough result.
         * @param deferrer                  Deferred handler.
         */
        inline constexpr Deduction defer(Deferrer&& deferrer) { return defer(passable(), std::move(deferrer)); }
        inline constexpr Deduction defer(Deduction&& deduction, Deferrer&& deferrer) {
            return m_world->m_deferred.emplace_back(std::move(deferrer)), std::move(deduction);
        }

        /**
         * @brief Handles running a complete type-audit.
         * @param tree                      Syntax tree node.
         * @param reporter                  Diagnostic reporter.
         */
        $::Ptr::Unique<Context> audit(const Syntax::Tree* tree, Diagnostic::Reporter* reporter = nullptr);

        /**
         * @brief Handles checking individual nodes.
         * @param node                      Node to check.
         * @param fallback                  Fallback type.
         */
        Deduction check(const Syntax::Node* node);
        Deduction check(const Syntax::Node* node, const Erased& fallback);

        /**
         * @brief Checks a sequence of nodes.
         * @param nodes                     Nodes to check.
         */
        Deduction check(const std::vector<Syntax::Node*>& nodes);

        /**
         * @brief Checks a sequence of explicit nodes.
         * @param nodes                     Nodes to check.
         */
        template <std::derived_from<Syntax::Node> T>
        inline constexpr void check(const std::vector<T*>& nodes) {
            for (const auto* node : nodes) check(node);
        }

        /**
         * @brief Handles instantiating a parameter list.
         * @param parameters                Parameters to instantiate.
         */
        Template check(const Syntax::Template& parameters);

        /**
         * @brief Handles instantiating
         * @param type                      Type to instantiate
         * @param arguments                 Generic arguments.
         */
        Erased instantiate(const Erased& type, const Syntax::Specialization& arguments);

        /**
         * @brief Handles branching decisions.
         * @param deduction                 Deduction details.
         * @param left                      Left-branch handler.
         * @param right                     Optional right-branch.
         */
        Deduction branch(Deduction&& deduction, Branch&& left, Branch&& right);

        /**
         * @brief Handles importing resources.
         * @param path                      Resource to import.
         * @param location                  Optional location.
         */
        const Context* import(const $::String::View& path, const Resource::Location& location = {});
        const Context* import(const $::URI::View& resource, const Resource::Location& location = {});

        /**
         * @brief Constructs a passable control-flow.
         * @param type                      Result type.
         */
        Deduction passable() const;
        Deduction passable(const Erased& type) const;

        /**
         * @brief Constructs an unreachable control-flow.
         * @param degree                    Reachability degree.
         * @param effect                    Control flow effect.
         */
        Deduction unreachable(Flow::Effect effect = Flow::Effect::NONE) const;
        Deduction unreachable(Flow::Degree degree, Flow::Effect effect = Flow::Effect::NONE) const;

        /**
         * @brief Declares code as unreachable/redundant.
         * @param node                      Node to make redundant.
         */
        Deduction redundant(const Syntax::Node* node);

        /**
         * @brief Declares a variable.
         * @param variable                      Variable to declare.
         */
        Erased declare(const Syntax::Variable* variable);

        /**
         * @brief Handles marking an identifier.
         * @param identifier                Identifier to mark.
         * @param entity                    Associated entity.
         * @param depth                     Current depth value.
         */
        void mark(const Syntax::Identifier* identifier, Entity* entity, Depth depth) const noexcept;

        /**
         * @brief Reports a diagnostic.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr Deduction report(Diagnostic::Code code, As&&... args) {
            return m_report(Resource::Stack(), code, std::forward<As>(args)...);
        }

        /**
         * @brief Reports a diagnostic.
         * @param location                  Resource location.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <std::derived_from<Resource::Location> T, class... As>
        inline constexpr Deduction report(const T& location, Diagnostic::Code code, As&&... args) {
            auto stack = location.anonymous() ? Resource::Stack() : Resource::Stack({ location });
            return m_report(stack, code, std::forward<As>(args)...);  // request from underlying
        }

        /**
         * @brief Reports a diagnostic.
         * @param range                     Resource range.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr Deduction report(const XLSP::Range& range, Diagnostic::Code code, As&&... args) {
            return report(Resource::Location(resource(), range), code, std::forward<As>(args)...);
        }

        /**
         * @brief Reports a diagnostic.
         * @param node                      Syntax node.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <std::derived_from<Syntax::Node> T, class... As>
        inline constexpr Deduction report(const T* node, Diagnostic::Code code, As&&... args) {
            return report(node->traits()->location(), code, std::forward<As>(args)...);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Reports a diagnostic.
         * @param stack                     Resource stack.
         * @param code                      Diagnostic code.
         * @param args                      Message arguments.
         */
        template <class... As>
        inline constexpr Deduction m_report(const Resource::Stack& stack, Diagnostic::Code code, As&&... args) {
            if (m_reporter) m_reporter->emit(stack, code, std::forward<As>(args)...);
            return passable($::New().shared<Failure>());  // bind a failure typing to be used
        }

        /**
         * @brief Handles making deductions from a branch.
         * @param branch                    Branch to execute.
         */
        $::Ptr::Unique<Flow::Control> m_using(Branch&& branch);

        /**
         * @brief Handles merging flows together.
         * @param left                      Left-most flow.
         * @param right                     Right-most flow.
         */
        $::Ptr::Unique<Flow::Control> m_merge(
            $::Ptr::Unique<Flow::Control>&& left, $::Ptr::Unique<Flow::Control>&& right) const noexcept;
    };

}  // namespace Forge::Type

#endif
