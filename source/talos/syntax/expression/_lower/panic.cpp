/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Panic, node, compiler, ) {
  $_UNUSED $_AUTO = compiler->trace(node);
  compiler->panic(node->value()); // bind
}
