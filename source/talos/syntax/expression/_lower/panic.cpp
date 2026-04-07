/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Panic, node, compiler, ) {
    $_UNUSED $_AUTO = compiler->trace(node);
    compiler->panic(node->value());  // bind
}
