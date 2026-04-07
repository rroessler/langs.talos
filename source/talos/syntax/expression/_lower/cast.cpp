/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Cast, node, compiler, destination) {
    // prepare the trace handler to be used
    $_UNUSED $_AUTO = compiler->trace(node);

    // get some information about the guard to be used
    auto guard = node->guard()->traits()->lattice();

    // if the guard is expected to be dynamic (eg: "Any") then we can ignore it
    if (guard.dynamic()) return compiler->lower(node->value(), destination);

    auto bx = Accumulator();  // prepare ax/bx
    auto ax = compiler->registers()->temporary();

    // lower the left-hand side and the right-hand side
    compiler->lower(node->value(), ax), compiler->lower(node->guard(), bx);

    // force a runtime guard to occur now as necessary
    compiler->plug<Syllable::TYPE_CAST>(destination, ax, bx);
}
