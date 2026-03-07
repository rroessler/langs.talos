/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Panic, panic, compiler, ) {
    $_UNUSED $_AUTO = compiler->trace(panic);
    compiler->panic(panic->value());
}
