/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Break, , ) {}
TALOS_MM_LINT_NODE(Continue, , ) {}

TALOS_MM_LINT_NODE(Return, node, analyzer) { analyzer->verify(node->value(), node); }
