/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Namespace, node, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // get the details of the namespace declaration
    auto [dest, leaked] = compiler->declare(node);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");
    auto treg = leaked ? compiler->registers()->temporary() : dest;

    // scope a module instance to be used now
    compiler->emit<Syllable::MODULE_OPEN>(treg);
    compiler->lower(node->block());
    compiler->emit<Syllable::MODULE_CLOSE>(treg);

    // post-emit the preamble for the namespace
    compiler->expose(node, treg);

    // lastly we want to emit the vreg depending on details
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, treg);
}
