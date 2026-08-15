/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Typed, node, analyzer) { analyzer->visit(node->value()); }
TALOS_MM_CHECK_NODE(Typed, node, analyzer) {
  $_UNUSED $_AUTO = analyzer->trace(node);
  auto result = analyzer->check(node->value());
  if (result.type->is<Type::Any>()) return result;
  return analyzer->instantiate(result.type, node->types());
}
