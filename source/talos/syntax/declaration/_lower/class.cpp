/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Class, node, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // get the location of the variable now
    auto [dest, leaked] = compiler->declare(node);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");

    // prepare some details about the class
    auto* parent = node->extends();
    auto treg = leaked ? Accumulator() : dest;

    // if we have an extension value, then resolve
    if (parent) compiler->lower(parent, treg);
    else compiler->emit<Syllable::LOAD_VOID>(treg);

    auto name = compiler->string(node->name());
    auto shape = compiler->shapes()->resolve(node);
    compiler->emit<Syllable::CLASS_MAKE>(treg, name, shape);

    // enqueue the class for compilation now
    compiler->emit<Syllable::CLASS_BIND>(treg, compiler->enqueue(node));

    // we want to update the current value details
    compiler->preamble(node, treg);

    // and handle assignment based on the leakage state
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, treg);
}
