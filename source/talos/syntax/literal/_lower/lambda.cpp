/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Lambda, lambda, compiler, destination) {
    // we need to manually emit as we should not enqueue/compile further if not needed at all
    if (!destination.nowhere()) compiler->emit<Syllable::CLOSURE_MAKE>(destination, compiler->enqueue(lambda));
}
