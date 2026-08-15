/// Talos Modules
#include "talos/bytecode/invoker.hpp"
#include "talos/bytecode/visitor.hpp"

//  PRIVATE METHODS  //

TALOS_MM_LOWER_NODE(Call, node, compiler, destination) {
  $_UNUSED $_AUTO = compiler->trace(node); // prepare trace
  auto invoker = Bytecode::Invoker(node->callee(), false);
  invoker.compile(compiler, destination, node->arguments());
}
