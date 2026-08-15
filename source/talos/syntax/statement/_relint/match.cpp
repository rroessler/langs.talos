/// Talos Includes
#include "talos/relint/visitor.hpp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Fallback, , ) {}

TALOS_MM_LINT_NODE(Query, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->verify(node->guards(), node);
  analyzer->verify(node->statement(), node);
}

TALOS_MM_LINT_NODE(Match, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->verify(node->value(), node);
  analyzer->verify(node->queries(), node);
}
