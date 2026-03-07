/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Enum, node, analyzer) { analyzer->verify(node->variants(), node); }

TALOS_MM_LINT_NODE(Variant, node, analyzer) {
    analyzer->verify(node->label(), node);
    analyzer->verify(node->value(), node);
}
