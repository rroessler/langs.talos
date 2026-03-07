/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Identifier, identifier, compiler, destination) {
    $_UNUSED $_AUTO = compiler->trace(identifier);
    auto extent = compiler->captures()->resolve(identifier);
    return compiler->load(identifier->name(), extent, destination);
}
