/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Continue, , ) {}
TALOS_MM_CHECK_NODE(Continue, node, analyzer) {
  Flow::Degree depth = analyzer->world()->loops();
  if (depth < 0) return analyzer->report(node, 2000601, "continue");
  return analyzer->unreachable(depth, Flow::Effect::LOOPS);
}
