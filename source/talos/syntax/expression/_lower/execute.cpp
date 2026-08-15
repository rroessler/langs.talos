/// Talos Modules
#include "talos/bytecode/invoker.hpp"
#include "talos/bytecode/visitor.hpp"

//  PRIVATE METHODS  //

TALOS_MM_LOWER_NODE(Execute, node, compiler, destination) {
  // prepare the trace to be used now as needed
  $_UNUSED $_AUTO = compiler->trace(node);

  // depending on our policy given, we should construct
  auto async = node->policy() == Function::Policy::ASYNC;

  // and implement our required invocation to be executed
  auto invoker = Bytecode::Invoker(node->callee(), async);
  invoker.compile(compiler, destination, node->arguments());
}
