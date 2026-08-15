/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Decorator, node, analyzer) { analyzer->verify(node->expression()); }
