#ifndef _FORGE_RELINT_SERVICE_HPP
#define _FORGE_RELINT_SERVICE_HPP

/// Forge Modules
#include "forge/crate/registry.hpp"
#include "forge/relint/hooks.hpp"

namespace Forge::Relint {

    /// @brief The linter service contains all available rules.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief The default options available.
        const Options* m_options = nullptr;

        /// @brief All available subscribed rules.
        $::Record<$::Ptr::Unique<Rule>> m_rules = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /**
         * @brief Handles subscribing rules.
         * @param rule                      Rule to subscribe.
         */
        inline constexpr bool subscribe($::Ptr::Unique<Rule>&& rule) {
            return m_rules.emplace(rule->documentation.identifier, std::move(rule)).second;
        }

        /**
         * @brief Handles subscribing rules.
         * @param identifier                Rule identifier.
         * @param rule                      Rule to subscribe.
         */
        inline constexpr bool subscribe(const $::String::Buffer& identifier, $::Ptr::Unique<Rule>&& rule) {
            return rule->documentation.identifier = identifier, subscribe(std::move(rule));
        }

        /**
         * @brief Handles resolving delegate hooks.
         * @param args                      Crate scanning arguments.
         */
        template <class... As>
        inline constexpr $::Ptr::Unique<Hooks> hooks(As&&... args) {
            return m_hooks(Crate::Registry::scan(std::forward<As>(args)...)->lint());
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles merging options with global ones.
         * @param options                   Options to merge with globals.
         */
        void m_merge(Options& options) const noexcept;

        /**
         * @brief Handles emplacing plugins.
         * @param options                   Options to update with plugins.
         */
        void m_plugins(Options& options) const noexcept;

        /**
         * @brief Handles setting all the recommended options.
         * @param options                   Options to set recommendations.
         */
        void m_recommends(Options& options) const noexcept;

        /**
         * @brief Handles merging, plugins and setting recommended settings.
         * @param options                   Options to merge.
         */
        Options& m_resolve(Options& options) const noexcept;

        /**
         * @brief Constructs hooks from the incoming options.
         * @param options                   Options to use.
         */
        $::Ptr::Unique<Hooks> m_hooks(Options options);
    };

}  // namespace Forge::Relint

#endif
