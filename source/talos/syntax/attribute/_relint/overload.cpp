/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Overload, node, analyzer) { analyzer->verify(node->signature(), node); }
