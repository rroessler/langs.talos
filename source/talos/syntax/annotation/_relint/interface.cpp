/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Interface, node, analyzer) { analyzer->verify(node->properties(), node); }
