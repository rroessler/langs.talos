#ifndef _FORGE_RELINT_RULE_HPP
#define _FORGE_RELINT_RULE_HPP

/// Forge Modules
#include "forge/forward/relint.hpp"

namespace Forge::Relint {

    /// @brief Handles dispatching rule factories.
    template <$::String::Literal N>
    void Register(Hooks* hooks, const Rule* rule);

    /// @brief Rule Documentation Details.
    struct Documentation {
        //  PROPERTIES  //

        /// @brief The associated rule identifier (no need to assign).
        $::String::Buffer identifier = "talos/unknown";

        /// @brief The baseline message format for a rule.
        $::String::Buffer message = "Rule error message...";

        /// @brief The documentation description for a rule.
        $::String::Buffer description = "Rule description...";

        /// @brief An associated resource buffer.
        $::URI::View resource = $::URI::Anonymous();
    };

    /// @brief Relint Rule Definition.
    struct Rule {
        //  PROPERTIES  //

        /// @brief Denotes if the rule is deprecated.
        bool deprecated = false;

        /// @brief Denotes if a rule is recommended.
        bool recommended = false;

        /// @brief Defaulted severity type.
        Severity severity = Severity::WARN;

        /// @brief Rule documentation structure.
        Documentation documentation = {};

        /// @brief Handles constructing rules.
        Factory factory = [](Hooks*, const Rule*) {};
    };

}  // namespace Forge::Relint

#endif
