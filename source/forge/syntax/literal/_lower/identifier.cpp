/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Identifier, identifier, compiler, destination) {
    $_UNUSED $_AUTO = compiler->trace(identifier);
    auto extent = compiler->captures()->resolve(identifier);
    return compiler->load(identifier->name(), extent, destination);
}
