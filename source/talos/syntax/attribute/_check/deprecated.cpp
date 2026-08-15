/// Talos Includes
#include "talos/variable/visitor.hpp"

/// Talos Includes
#include "talos/type/_inline/type.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CAPTURE_NODE(Deprecated, , ) {}

TALOS_MM_CHECK_NODE(Deprecated, node, analyzer) {
  // get the available world instance
  auto *world = analyzer->world();

  // update the current deprecation details
  auto *entity = world->preamble();
  entity->deprecated(node->message());

  // and declare as passable now
  return analyzer->passable();
}
