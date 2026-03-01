/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Caret, node, analyzer) {
    Type::Erased callee = analyzer->world()->callee();  // validate now as needed
    return callee ? analyzer->passable(callee) : analyzer->report(node, 3000551);
}
