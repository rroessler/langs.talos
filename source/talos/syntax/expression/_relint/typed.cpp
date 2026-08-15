/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Typed, node, analyzer) {
  analyzer->verify(node->value(), node);
  analyzer->verify(node->types(), node);
}
