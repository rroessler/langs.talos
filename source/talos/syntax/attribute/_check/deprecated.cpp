/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Deprecated, node, analyzer) {
    // get the available world instance
    auto* world = analyzer->world();

    // get the underlying entity instance
    auto* entity = world->preamble();

    // update the current deprecation details
    entity->deprecated() = node->message();

    // and declare as passable now
    return analyzer->passable();
}
