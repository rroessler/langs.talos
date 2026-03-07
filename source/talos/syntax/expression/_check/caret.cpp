/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Caret, node, analyzer) {
    Type::Erased callee = analyzer->world()->callee();  // validate now as needed
    return callee ? analyzer->passable(callee) : analyzer->report(node, 3000551);
}
