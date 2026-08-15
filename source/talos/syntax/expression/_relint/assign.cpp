/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Assign, node, analyzer) {
  analyzer->verify(node->target(), node);
  analyzer->verify(node->value(), node);
}
