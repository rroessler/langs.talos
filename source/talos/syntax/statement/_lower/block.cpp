/// Talos Modules
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_LOWER_NODE(Block, node, compiler, ) {
    // ignore if the node is currently empty
    if (node->empty()) return;

    // trace the incoming binary node now
    $_UNUSED $_AUTO = compiler->scope();
    $_UNUSED $_AUTO = compiler->disposable(node);

    // and lower each of the incoming statements as well
    for (const auto& statement : node->statements()) compiler->lower(statement);
}
