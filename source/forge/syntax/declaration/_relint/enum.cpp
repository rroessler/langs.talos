/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Enum, node, analyzer) { analyzer->verify(node->variants(), node); }

FORGE_MM_LINT_NODE(Variant, node, analyzer) {
    analyzer->verify(node->label(), node);
    analyzer->verify(node->value(), node);
}
