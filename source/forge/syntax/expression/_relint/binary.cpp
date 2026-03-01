/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Binary, node, analyzer) {
    analyzer->verify(node->left(), node);
    analyzer->verify(node->right(), node);
}
