/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Caret, , ) {}
TALOS_MM_CHECK_NODE(Caret, node, analyzer) {
  Type::Erased callee = analyzer->world()->callee(); // validate now as needed
  return callee ? analyzer->passable(callee) : analyzer->report(node, 3000551);
}
