/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Numeric, numeric, compiler, destination) {
    // ignore if there is no sink to output to
    if (destination.nowhere()) return;

    // prepare the value to be used now
    auto value = numeric->value();

    // handle consistent values now
    if (value == 0) return compiler->emit<Syllable::LOAD_ZERO>(destination);
    else if (value == 1) return compiler->emit<Syllable::LOAD_ONE>(destination);

    // prepare the constant to be used now
    auto constant = compiler->constant(Number::Tagged(value));
    compiler->emit<Syllable::LOAD_CONST>(destination, constant);
}
