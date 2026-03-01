/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Break, , ) {}
FORGE_MM_LINT_NODE(Continue, , ) {}

FORGE_MM_LINT_NODE(Return, node, analyzer) { analyzer->verify(node->value(), node); }
