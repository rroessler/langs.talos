/// Talos Modules
#include "talos/module/archived.hpp"
#include "talos/module/interface.hpp"

/// Metadata Modules
#include "talos/bytecode/metadata.hpp"

//  PUBLIC METHODS  //

template <>
void Talos::Module::Interface::dump<Talos::Module::Dump::SYNTAX>() const noexcept {
    // ignore for non-script values now
    if (!is<Script>()) return;

    // show the baseline dump details now
    $::IO::eprintln("\n===== Syntax Dump '{0}' =====\n", $::Path::relative(resource().body()).string());
}

template <>
void Talos::Module::Interface::dump<Talos::Module::Dump::TYPEDEFS>() const noexcept {}

template <>
void Talos::Module::Interface::dump<Talos::Module::Dump::BYTECODE>() const noexcept {
    // ignore for non-script values now
    if (!(is<Script>() || is<Archived>())) return;

    // show the baseline dump details now
    $::IO::eprintln("\n===== Bytecode Dump '{0}' =====\n", $::Path::relative(resource().body()).string());

    // print the arena if it has some functions
    auto* arena = metadata<Phase::COMPILED>()->arena();
    if (arena->functions.size()) $::IO::eprintln("{0}\n", *arena);
}
