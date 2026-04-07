/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Block, node, analyzer) {
    // ignore if there are no statements available
    if (node->empty()) return analyzer->passable();

    // otherwise attempt scoping the result now
    $_UNUSED $_AUTO = analyzer->scope();
    return analyzer->check(node->statements());
}
