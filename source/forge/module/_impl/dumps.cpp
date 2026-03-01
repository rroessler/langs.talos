/// Forge Modules
#include "forge/module/archived.hpp"
#include "forge/module/interface.hpp"

/// Metadata Modules
#include "forge/bytecode/metadata.hpp"

//  PUBLIC METHODS  //

template <>
void Forge::Module::Interface::dump<Forge::Module::Dump::SYNTAX>() const noexcept {
    // ignore for non-script values now
    if (!is<Script>()) return;

    // show the baseline dump details now
    $::IO::eprintln("\n===== Syntax Dump '{0}' =====\n", $::Path::relative(resource().body()).string());
}

template <>
void Forge::Module::Interface::dump<Forge::Module::Dump::TYPEDEFS>() const noexcept {}

template <>
void Forge::Module::Interface::dump<Forge::Module::Dump::BYTECODE>() const noexcept {
    // ignore for non-script values now
    if (!(is<Script>() || is<Archived>())) return;

    // show the baseline dump details now
    $::IO::eprintln("\n===== Bytecode Dump '{0}' =====\n", $::Path::relative(resource().body()).string());

    // print the arena if it has some functions
    auto* arena = metadata<Phase::COMPILED>()->arena();
    if (arena->functions.size()) $::IO::eprintln("{0}\n", *arena);
}
