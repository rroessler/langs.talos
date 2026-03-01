/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Accessor, node, analyzer) {
    analyzer->verify(node->parent(), node);
    analyzer->verify(node->field(), node);
}
