/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Tuple, node, compiler, destination) {
    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->trace(node);

    // if empty, then construct an empty instance
    if (node->empty()) return compiler->plug<Syllable::LIST_EMPTY>(destination);

    // prepare a suitable arguments list
    auto arguments = compiler->registers()->list();

    // construct the list to be used now
    for (const auto& element : node->elements()) compiler->lower(element, arguments.grow());
    compiler->plug<Syllable::LIST_MAKE>(destination, arguments);  // and make the list now
}
