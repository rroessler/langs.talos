/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Assign, node, analyzer) {
    analyzer->verify(node->target(), node);
    analyzer->verify(node->value(), node);
}
