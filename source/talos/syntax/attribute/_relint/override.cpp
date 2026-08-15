/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Override, node, analyzer) { analyzer->verify(node->target(), node); }
