/// Forge Modules
#include "forge/bytecode/invoker.hpp"
#include "forge/bytecode/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_LOWER_NODE(Call, node, compiler, destination) {
    $_UNUSED $_AUTO = compiler->trace(node);  // prepare the baseline trace to be used
    Bytecode::Invoker(node->callee()).invoke(compiler, destination, node->arguments());
}
