#ifndef _TALOS_RELINT_ANALYZER_HPP
#define _TALOS_RELINT_ANALYZER_HPP

/// Talos Modules
#include "talos/relint/context.hpp"
#include "talos/relint/options.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Relint {

    /// @brief Linter Analyzer.
    struct Analyzer : public XI::Define<Analyzer, XI::Unique, Context> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an analyzer instance.
         * @param services                  Services container.
         */
        explicit Analyzer();
        explicit Analyzer(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief Current analyzer metadata.
        inline constexpr Metadata* metadata() noexcept { return m_mirrors.get(); }

        /// @brief Handles scoping deferred callbacks.
        inline constexpr auto scope() {
            return $::Functor::Defer([&] {
                auto deferred = std::move(m_deferred);  // remove
                for (auto&& deferrer : deferred) deferrer(this);
            });
        }

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
         * @brief Handles deferring linting.
         * @param deferrer                  Deferred handler.
         */
        inline constexpr void defer(Deferrer&& deferrer) { m_deferred.emplace_back(std::move(deferrer)); }

        /**
         * @brief Handles running a complete linter-audit.
         * @param tree                      Syntax tree node.
         * @param reporter                  Diagnostic reporter.
         */
        $::Ptr::Unique<Metadata> audit(const Syntax::Tree* tree, Diagnostic::Reporter* reporter);

        /**
         * @brief Handles linting a singular node.
         * @param node                      Node to lint.
         * @param parent                    Parent to bind.
         */
        Mirror* verify(const Syntax::Node* node, const Syntax::Node* parent = nullptr);

        /**
         * @brief Handles linting a multiple nodes.
         * @param nodes                     Nodes to lint.
         * @param parent                    Parent to bind.
         */
        template <std::derived_from<Syntax::Node> T>
        inline constexpr std::vector<Mirror*> verify(
            const std::vector<T*>& nodes, const Syntax::Node* parent = nullptr) {
            auto predicate = [&](const T* node) { return verify(node, parent); };
            return $::Ranges::To(nodes | std::views::transform(predicate));
        }

        /**
         * @brief Handles traversing a node.
         * @param node                      Node to traverse.
         */
        void traverse(const Syntax::Node* node);

        /**
         * @brief Handles traversing a multiple nodes.
         * @param nodes                     Nodes to lint.
         */
        template <std::derived_from<Syntax::Node> T>
        inline constexpr void traverse(const std::vector<T*>& nodes) {
            for (const auto* node : nodes) traverse(node);
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles finalizing mirror data (eg: comments, ...).
         * @param mirror                    Mirror to finalize.
         */
        void m_finalize(Mirror* mirror);
    };

}  // namespace Talos::Relint

#endif
