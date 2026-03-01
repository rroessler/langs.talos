/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Accessor, accessor, compiler, destination) {
    // ensure we load the parent into the accumulator
    compiler->lower(accessor->parent(), destination);

    // ignore loading the field if the destination is nowhere
    if (destination.nowhere()) return;

    // prepare the trace for the node now
    $_UNUSED $_AUTO = compiler->trace(accessor);

    // attempt loading the field as necessary now
    auto symbol = compiler->symbol(accessor->field()->name());
    compiler->emit<Syllable::LOAD_FIELD>(destination, destination, symbol);
}
