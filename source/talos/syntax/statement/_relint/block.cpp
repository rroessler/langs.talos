/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Block, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->verify(node->statements(), node);
}
