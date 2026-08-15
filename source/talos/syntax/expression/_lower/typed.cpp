/// Talos Modules
#include "talos/bytecode/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Typed, node, compiler, destination) { compiler->lower(node->value(), destination); }
