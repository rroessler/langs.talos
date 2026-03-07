/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Typed, node, analyzer) {
    analyzer->verify(node->value(), node);
    analyzer->verify(node->types(), node);
}
