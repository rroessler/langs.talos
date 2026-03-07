/// Talos Modules
#include "talos/bytecode/invoker.hpp"
#include "talos/bytecode/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_LOWER_NODE(Call, node, compiler, destination) {
    $_UNUSED $_AUTO = compiler->trace(node);  // prepare the baseline trace to be used
    Bytecode::Invoker(node->callee()).invoke(compiler, destination, node->arguments());
}
