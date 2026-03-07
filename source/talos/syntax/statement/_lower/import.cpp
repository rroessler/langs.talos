/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Import, import, compiler, destination) {
    // ensure we trace the import execution
    $_UNUSED $_AUTO = compiler->trace(import);

    // get some of the baseline details
    auto patterns = import->patterns();
    auto* captures = compiler->captures();
    auto* registers = compiler->registers();

    // prepare the wildcard details to be used
    auto wildcard = Bytecode::Declaration({}, false);

    // if we have a wildcard import, then ensure we store properly
    if (import->wildcard()) wildcard = compiler->declare(patterns.at(0));

    // prepare the sink for the import to go to
    if (wildcard.second) destination = Accumulator();
    else if (import->wildcard()) destination = wildcard.first;
    else if (destination.nowhere()) destination = Accumulator();

    // attempt handling the incoming import now
    compiler->import(destination, import->path());

    // if exported then we need to re-export at our desired location
    if (import->exported()) {
        auto name = compiler->string(patterns.at(0)->name());  // prepare now
        return compiler->emit<Syllable::MODULE_EXPORT>(destination, name);
    }

    // if leaked, then we need to store properly
    if (wildcard.second) compiler->emit<Syllable::STORE_CONTEXT>(wildcard.first, destination);

    // stop if there are no patterns or just a wildcard handler
    if (patterns.empty() || import->wildcard()) return;

    // declare all the patterns to be available
    for (const auto& pattern : patterns) {
        $_UNUSED $_AUTO = compiler->trace(pattern);
        auto [vreg, leaked] = compiler->declare(pattern);

        // ensure we get some suitably details to be used
        auto index = compiler->symbol(pattern->name());
        auto treg = leaked ? registers->temporary() : vreg;

        // we attempt loading the field from the module and store it
        compiler->emit<Syllable::LOAD_FIELD>(treg, destination, index);
        compiler->store(pattern->name(), captures->resolve(pattern), treg);
    }
}
