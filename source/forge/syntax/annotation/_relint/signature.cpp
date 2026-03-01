/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Parameters, node, analyzer) { analyzer->verify(node->list(), node); }

FORGE_MM_LINT_NODE(Constructor, node, analyzer) {
    analyzer->verify(node->generics(), node);
    analyzer->verify(node->parameters(), node);
}

FORGE_MM_LINT_NODE(Signature, node, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(node->prototype(), node);
    analyzer->verify(node->returns(), node);
}
