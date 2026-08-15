/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Constructor, node, analyzer) {
  analyzer->visit(node->generics());
  analyzer->visit(node->parameters());
}

TALOS_MM_CHECK_NODE(Constructor, node, analyzer) {
  // get the current generics to be used now
  auto constraints = analyzer->check(node->generics());

  // attempt resolving the underlying parameters
  auto callable = analyzer->check(node->parameters()).type->as<Type::Callable>();

  // and construct the return typing based on the total constraints
  if (constraints.empty()) return analyzer->passable(callable);
  else return Type::New::generic(callable, constraints);
}
