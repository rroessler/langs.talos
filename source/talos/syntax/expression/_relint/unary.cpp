/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Unary, node, analyzer) { analyzer->verify(node->operand(), node); }
