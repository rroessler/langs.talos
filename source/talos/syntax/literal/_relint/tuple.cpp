/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Tuple, node, analyzer) { analyzer->verify(node->elements(), node); }
