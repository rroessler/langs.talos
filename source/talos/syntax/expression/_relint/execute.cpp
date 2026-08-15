/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Execute, node, analyzer) { analyzer->verify(node->invocation(), node); }
