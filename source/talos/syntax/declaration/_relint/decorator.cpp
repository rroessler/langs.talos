/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Decorator, node, analyzer) { analyzer->report(node, 9000002, "Relint::Visitor"); }
