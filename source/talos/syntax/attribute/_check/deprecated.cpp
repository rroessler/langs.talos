/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Deprecated, node, analyzer) { return analyzer->report(node, 9000002, "Type::Visitor"); }
