/// Talos Modules
#include "talos/relint/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LINT_NODE(Block, block, analyzer) {
    $_UNUSED $_AUTO = analyzer->scope();
    analyzer->verify(block->statements(), block);
}
