/// Talos Includes
#include "talos/relint/service.hpp"
#include "talos/async/service.hpp"
#include "talos/crate/registry.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/runtime/options.hpp"

/// Relint Includes
#include "talos/relint/_inline/rules.ipp"

//  CONSTRUCTORS  //

Talos::Relint::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Relint::Service::Service(XI::Container *services) :
    m_services(services), m_options(&services->get<Runtime::Options>()->linter) {
#define X(N, ...) subscribe($::Unique::New<Rule>(Register<Label::N>::define()));
  TALOS_XX_RELINT_RULES(X)
#undef X
}

//  PRIVATE METHODS  //

void Talos::Relint::Service::m_merge(Options &options) const noexcept {
  for (const auto &[identifier, severity] : m_options->rules) options.rules.try_emplace(identifier, severity);
}

void Talos::Relint::Service::m_plugins(Options &options) noexcept {
  // prepare the baseline services to be used
  Async::Service *async = *m_services;

  // iterate over the available plugins now to be used
  for (const auto &plugin : options.plugins) {
    // attempt importing the plugin instance
    auto result = async->isolate()->import(plugin);

    // only bind the result if it is valid here
    if (result.pointer().okay()) m_subscribe(result, options);

    /// TODO: otherwise we need to prepare a failure
  }
}

void Talos::Relint::Service::m_recommends(Options &options) const noexcept {
  // prepare the baseline rules to be appended here
  for (const auto &rule : m_rules | std::views::values) {
    const auto &identifier = rule->documentation.identifier;
    options.rules.try_emplace(identifier, rule->severity);
  }

  // also prepare the incoming recommended overrides to be used
#define TALOS_XX_DIAGNOSTIC_RECOMMENDS(N, S, ...) options.overrides.try_emplace(N, Severity::S);
#include "talos/relint/_defines/overrides.def"
}

Talos::Relint::Options &Talos::Relint::Service::m_resolve(Options &options) noexcept {
  return m_merge(options), m_plugins(options), m_recommends(options), options;
}

void Talos::Relint::Service::m_subscribe(const Value::Any &, Options &) noexcept {}

$::Unique::Pointer<Talos::Relint::Hooks> Talos::Relint::Service::m_hooks(Options options) noexcept {
  // resolve the options to be used
  options = m_resolve(options);

  // construct hooks with given options
  auto hooks = $::Unique::New<Hooks>(options);

  // construct all the necessary rules to be used
  for (const auto &rule : m_rules | std::views::values) {
    // ignore the rule if not actually requested at all
    if (!options.rules.contains(rule->documentation.identifier)) continue;

    // launch the factory if necessary to do so
    if (rule->factory) rule->factory(hooks.get(), rule.get());
  }

  // and return the resulting hooks to be used
  return hooks;
}
