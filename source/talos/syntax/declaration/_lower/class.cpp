/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_UNIMPLEMENTED(Header, , compiler, )

TALOS_MM_LOWER_NODE(Class, node, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // get the location of the variable now
    auto [dest, leaked] = compiler->declare(node);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");

    // prepare some details about the class
    auto treg = leaked ? Accumulator() : dest;

    // enqueue the underlying constructor
    auto constructor = compiler->enqueue(node);

    // prepare the baseline class instance to be used
    auto name = compiler->string(node->name());
    auto shape = compiler->shapes()->resolve(node);

    // prepare the baseline register now as well
    if (auto* base = node->base()) compiler->lower(base, treg);
    else compiler->emit<Syllable::LOAD_VOID>(treg);  // default

    // enqueue the class for compilation now
    compiler->emit<Syllable::CLASS_MAKE>(treg, name, shape);
    compiler->emit<Syllable::CLASS_BIND>(treg, constructor);

    // we want to update the current value details
    compiler->preamble(node, treg);

    // and handle assignment based on the leakage state
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, treg);
}
