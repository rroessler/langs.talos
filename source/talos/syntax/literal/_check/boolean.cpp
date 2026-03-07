/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(True, , ) { return { Type::Builder::boolean() }; }
TALOS_MM_CHECK_NODE(False, , ) { return { Type::Builder::boolean() }; }
