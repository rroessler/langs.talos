/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Panic, panic, compiler, ) {
    $_UNUSED $_AUTO = compiler->trace(panic);
    compiler->panic(panic->value());
}
