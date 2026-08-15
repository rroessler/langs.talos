/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Infer, node, analyzer) {
  analyzer->verify(node->value(), node);
  analyzer->verify(node->guard(), node);
}
