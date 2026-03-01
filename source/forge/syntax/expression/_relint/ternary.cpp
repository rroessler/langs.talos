/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Ternary, node, analyzer) {
    analyzer->verify(node->condition(), node);
    analyzer->verify(node->consequence(), node);
    analyzer->verify(node->alternative(), node);
}
