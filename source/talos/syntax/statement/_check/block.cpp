/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Block, node, analyzer) {
  if (node->empty()) return; // ignore empty
  $_UNUSED $_AUTO = analyzer->scope();
  analyzer->visit(node->statements());
}

TALOS_MM_CHECK_NODE(Block, node, analyzer) {
  // ignore if there are no statements available
  if (node->empty()) return analyzer->passable();

  // otherwise attempt scoping the result now
  $_UNUSED $_AUTO = analyzer->scope();
  return analyzer->check(node->statements());
}
