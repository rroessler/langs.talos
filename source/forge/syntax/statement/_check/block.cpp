/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Block, block, analyzer) {
    // ignore if there are no statements available
    if (block->empty()) return analyzer->passable();

    // otherwise attempt scoping the result now
    $_UNUSED $_AUTO = analyzer->scope();
    return analyzer->check(block->statements());
}
