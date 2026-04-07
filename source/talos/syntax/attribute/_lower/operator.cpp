/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Operator, node, compiler, destination) {
    // ensure the incoming destination is valid
    if (destination.nowhere()) return;

    // prepare a temporary register for the incoming value
    auto treg = compiler->registers()->temporary();

    // lower the incoming target to be updated
    compiler->lower(node->target(), treg);

    // convert the operator kind into an operand
    auto kind = static_cast<Bytecode::Index::Encoded>(node->kind());

    // assign the operator as necessary now
    compiler->emit<Syllable::OBJECT_ATTR>(destination, treg, kind);
}
