/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(For, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->iterable(), node);
    analyzer->verify(node->statement(), node);
}

FORGE_MM_LINT_NODE(Loop, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->condition(), node);
    analyzer->verify(node->statement(), node);
}
