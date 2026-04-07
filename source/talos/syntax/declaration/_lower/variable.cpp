/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Variable, node, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // get the location of the variable now
    auto [dest, leaked] = compiler->declare(node);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");

    // prepare our initializer for the variable now
    auto ireg = leaked ? Accumulator() : dest;
    auto* initializer = node->initializer();
    if (initializer) compiler->lower(initializer, ireg);

    // we want to update the current value details
    compiler->preamble(node, ireg);

    // if the instance is disposable, then attach to frame
    if (node->disposable()) compiler->emit<Syllable::DISPOSE_DEFER>(ireg);

    // and handle assignment based on the leakage state
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, ireg);
}
