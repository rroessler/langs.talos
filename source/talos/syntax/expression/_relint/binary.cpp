/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Binary, node, analyzer) {
  analyzer->verify(node->left(), node);
  analyzer->verify(node->right(), node);
}
