/// Talos Modules
#include "talos/relint/options.hpp"

//  PROPERTIES  //

#define TALOS_XX_RELINT_ALIAS(N, C, ...) { N, C },
static $::Dict<Talos::Diagnostic::Code> g_aliases = {
#include "talos/relint/_defines/aliases.def"
};

//  PRIVATE METHODS  //

void Talos::Relint::Options::m_overrides(Options& options) {
    for (const auto& [identifier, code] : g_aliases) {
        if (!options.rules.contains(identifier)) continue;  // not found
        options.overrides.try_emplace(code, options.rules.at(identifier));
    }
}
