/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Lambda, lambda, compiler, destination) {
    if (!destination.nowhere()) compiler->emit<Syllable::CLOSURE_MAKE>(destination, compiler->enqueue(lambda));
}
