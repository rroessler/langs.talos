/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Call, node, analyzer) {
  analyzer->verify(node->callee(), node);
  analyzer->verify(node->arguments(), node);
}
