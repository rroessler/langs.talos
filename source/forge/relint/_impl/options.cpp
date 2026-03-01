/// Forge Modules
#include "forge/relint/options.hpp"

//  PROPERTIES  //

#define FORGE_XX_RELINT_ALIAS(N, C, ...) { N, C },
static $::Dict<Forge::Diagnostic::Code> g_aliases = {
#include "forge/relint/_defines/aliases.def"
};

//  PRIVATE METHODS  //

void Forge::Relint::Options::m_overrides(Options& options) {
    for (const auto& [identifier, code] : g_aliases) {
        if (!options.rules.contains(identifier)) continue;  // not found
        options.overrides.try_emplace(code, options.rules.at(identifier));
    }
}
