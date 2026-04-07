/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Infer, node, compiler, destination) {
    // prepare the trace handler to be used
    $_UNUSED $_AUTO = compiler->trace(node);

    // get some information about the cast now
    auto guard = node->guard()->traits()->lattice();

    // if the guard is dynamic, then we can return a constant result immediately
    if (guard.dynamic()) {
        if (node->negate()) return compiler->plug<Syllable::LOAD_FALSE>(destination);
        else return compiler->plug<Syllable::LOAD_TRUE>(destination);  // always truthy
    }

    auto bx = Accumulator();  // prepare ax/bx
    auto ax = compiler->registers()->temporary();

    // lower the left-hand side and the right-hand side
    compiler->lower(node->value(), ax), compiler->lower(node->guard(), bx);

    // force a runtime guard to occur now as necessary
    compiler->plug<Syllable::TYPE_GUARD>(destination, ax, bx);

    // handle the negation of results if necessary
    if (node->negate()) compiler->emit<Syllable::UNOP_NOT>(destination, destination);
}
