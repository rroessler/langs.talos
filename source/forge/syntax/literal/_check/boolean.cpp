/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(True, , ) { return { Type::Builder::boolean() }; }
FORGE_MM_CHECK_NODE(False, , ) { return { Type::Builder::boolean() }; }
