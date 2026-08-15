/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Overload, node, analyzer) { analyzer->visit(node->signature()); }

TALOS_MM_CHECK_NODE(Overload, node, analyzer) {
  return analyzer->report(node, 9000002, "Analyzer.check(Syntax::Overload)");
}
