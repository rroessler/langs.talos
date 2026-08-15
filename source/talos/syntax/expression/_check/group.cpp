/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Group, node, analyzer) { analyzer->visit(node->value()); }
TALOS_MM_CHECK_NODE(Group, node, analyzer) { return analyzer->check(node->value()); }
