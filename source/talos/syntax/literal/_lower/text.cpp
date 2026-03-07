/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Text, text, compiler, destination) {
    if (destination.nowhere()) return;  // we can suitably ignore if going nowhere
    compiler->emit<Syllable::STRING_MAKE>(destination, compiler->string(text->buffer()));
}
