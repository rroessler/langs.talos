/// Talos Modules
#include "talos/relint/service.hpp"
#include "talos/crate/registry.hpp"
#include "talos/runtime/container.hpp"

//  PROPERTIES  //

// we pre-declare all the template specializations here
#define TALOS_MM_RELINT_REGISTER
#include "talos/relint/_inline/rules.ipp"

//  CONSTRUCTORS  //

Talos::Relint::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Relint::Service::Service(XI::Container* services) : m_options(&services->get<Runtime::Options>()->linter) {
#define TALOS_MM_RELINT_DEFINE(N, ...) subscribe(N, $::New().unique<Rule>(Rule __VA_ARGS__));
#include "talos/relint/_inline/rules.ipp"  // subscribe all the available builtin rules
}

//  PRIVATE METHODS  //

void Talos::Relint::Service::m_merge(Options& options) const noexcept {
    for (const auto& [identifier, severity] : m_options->rules) options.rules.try_emplace(identifier, severity);
}

void Talos::Relint::Service::m_plugins(Options&) const noexcept {
    /// TODO: implement plugin receivers
}

void Talos::Relint::Service::m_recommends(Options& options) const noexcept {
    // prepare the baseline rules to be appended here
    for (const auto& rule : m_rules | std::views::values) {
        const auto& identifier = rule->documentation.identifier;
        options.rules.try_emplace(identifier, rule->severity);
    }

    // also prepare the incoming recommended overrides to be used
#define TALOS_XX_DIAGNOSTIC_RECOMMENDS(N, S, ...) options.overrides.try_emplace(N, Severity::S);
#include "talos/relint/_defines/overrides.def"
}

Talos::Relint::Options& Talos::Relint::Service::m_resolve(Options& options) const noexcept {
    return m_merge(options), m_plugins(options), m_recommends(options), options;
}

$::Ptr::Unique<Talos::Relint::Hooks> Talos::Relint::Service::m_hooks(Options options) {
    // resolve the options to be used
    options = m_resolve(options);

    // construct hooks with given options
    auto hooks = $::New().unique<Hooks>(options);

    // construct all the necessary rules to be used
    for (const auto& rule : m_rules | std::views::values) {
        // ignore the rule if not actually requested at all
        if (!options.rules.contains(rule->documentation.identifier)) continue;

        // launch the factory if necessary to do so
        if (rule->factory) rule->factory(hooks.get(), rule.get());
    }

    // and return the resulting hooks to be used
    return hooks;
}
