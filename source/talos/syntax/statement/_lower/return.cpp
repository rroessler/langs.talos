/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Return, node, compiler, ) { compiler->returns(node->value()); }
