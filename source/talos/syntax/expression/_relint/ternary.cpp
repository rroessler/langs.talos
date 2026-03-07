/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Ternary, node, analyzer) {
    analyzer->verify(node->condition(), node);
    analyzer->verify(node->consequence(), node);
    analyzer->verify(node->alternative(), node);
}
