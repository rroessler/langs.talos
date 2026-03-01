/// Forge Modules
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

FORGE_MM_LOWER_NODE(Block, block, compiler, ) {
    // ignore if the block is currently empty
    if (block->empty()) return;

    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->scope();

    // and lower each of the incoming statements as well
    for (const auto& statement : block->statements()) compiler->lower(statement);
}
