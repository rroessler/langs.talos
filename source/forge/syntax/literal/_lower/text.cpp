/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Text, text, compiler, destination) {
    if (destination.nowhere()) return;  // we can suitably ignore if going nowhere
    compiler->emit<Syllable::STRING_MAKE>(destination, compiler->string(text->buffer()));
}
