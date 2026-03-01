/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Typed, node, analyzer) {
    analyzer->verify(node->value(), node);
    analyzer->verify(node->types(), node);
}
