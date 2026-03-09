/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Identifier, identifier, compiler, destination) {
    // declare a trace to be used
    $_UNUSED $_AUTO = compiler->trace(identifier);

    // we should be able to suitable plug the current self value
    if (identifier->self()) return compiler->plug<Syllable::LOAD_SELF>(destination);

    // handle regular variables now
    auto extent = compiler->captures()->resolve(identifier);
    return compiler->load(identifier->name(), extent, destination);
}
