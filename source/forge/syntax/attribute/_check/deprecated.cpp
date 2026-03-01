/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Deprecated, node, analyzer) { return analyzer->report(node, 9000002, "Type::Visitor"); }
