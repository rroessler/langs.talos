/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Cast, cast, compiler, destination) {
    // prepare the trace handler to be used
    $_UNUSED $_AUTO = compiler->trace(cast);

    // get some information about the guard to be used
    auto guard = cast->guard()->traits()->lattice();

    // if the guard is expected to be dynamic (eg: "Any") then we can ignore it
    if (guard.dynamic()) return compiler->lower(cast->value(), destination);

    auto bx = Accumulator();  // prepare ax/bx
    auto ax = compiler->registers()->temporary();

    // lower the left-hand side and the right-hand side
    compiler->lower(cast->value(), ax), compiler->lower(cast->guard(), bx);

    // force a runtime guard to occur now as necessary
    compiler->plug<Syllable::TYPE_CAST>(destination, ax, bx);
}
