/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Variable, variable, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(variable);

    // get the location of the variable now
    auto [dest, leaked] = compiler->declare(variable);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");

    // prepare our initializer for the variable now
    auto ireg = leaked ? Accumulator() : dest;
    auto* initializer = variable->initializer();
    if (initializer) compiler->lower(initializer, ireg);

    // we want to update the current value details
    compiler->preamble(variable, ireg);

    // if the instance is disposable, then attach to frame
    if (variable->disposable()) compiler->emit<Syllable::DISPOSE_DEFER>(ireg);

    // and handle assignment based on the leakage state
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, ireg);
}
