/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Panic, node, analyzer) { analyzer->verify(node->value(), node); }
