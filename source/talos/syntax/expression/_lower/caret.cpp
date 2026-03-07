/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Caret, , compiler, destination) {
    compiler->plug<Syllable::CLOSURE_MAKE>(destination, compiler->queue()->size());
}
