/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Parameters, node, analyzer) { analyzer->verify(node->list(), node); }

TALOS_MM_LINT_NODE(Constructor, node, analyzer) {
    analyzer->verify(node->generics(), node);
    analyzer->verify(node->parameters(), node);
}

TALOS_MM_LINT_NODE(Signature, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->prototype(), node);
    analyzer->verify(node->returns(), node);
}
