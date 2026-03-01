/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Call, node, analyzer) {
    analyzer->verify(node->callee(), node);
    analyzer->verify(node->arguments(), node);
}
