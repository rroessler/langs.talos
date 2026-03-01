/// Forge Modules
#include "forge/relint/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LINT_NODE(Block, block, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(block->statements(), block);
}
