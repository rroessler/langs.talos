/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Namespace, declaration, compiler, ) {
    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(declaration);

    // get the details of the namespace declaration
    auto [dest, leaked] = compiler->declare(declaration);
    $_ASSERT(!dest.nowhere(), "Declaration does not exist?");
    auto treg = leaked ? compiler->registers()->temporary() : dest;

    // scope a module instance to be used now
    compiler->emit<Syllable::MODULE_OPEN>(treg);
    compiler->lower(declaration->block());
    compiler->emit<Syllable::MODULE_CLOSE>(treg);

    // post-emit the preamble for the namespace
    compiler->expose(declaration, treg);

    // lastly we want to emit the vreg depending on details
    if (leaked) compiler->emit<Syllable::STORE_CONTEXT>(dest, treg);
}
