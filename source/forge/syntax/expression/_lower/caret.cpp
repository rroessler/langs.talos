/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Caret, , compiler, destination) {
    compiler->plug<Syllable::CLOSURE_MAKE>(destination, compiler->queue()->size());
}
