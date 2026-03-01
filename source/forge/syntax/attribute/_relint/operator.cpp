/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Operator, node, analyzer) { analyzer->report(node, 9000002, "Relint::Visitor"); }
