/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Panic, node, analyzer) { analyzer->visit(node->value()); }
TALOS_MM_CHECK_NODE(Panic, node, analyzer) {
  // push the necessary traces for analyzing
  $_UNUSED $_AUTO = analyzer->trace(node);

  // forcibly check the incoming value to be used now
  analyzer->check(node->value());

  // and declare as currently reachable now
  return analyzer->unreachable();
}
