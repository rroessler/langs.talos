/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(For, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->iterable(), node);
    analyzer->verify(node->statement(), node);
}

TALOS_MM_LINT_NODE(Loop, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->condition(), node);
    analyzer->verify(node->statement(), node);
}
