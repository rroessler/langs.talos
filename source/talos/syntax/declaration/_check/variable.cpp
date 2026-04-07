/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Variable, node, analyzer) {
    // prepare the base variable report to be used
    $_UNUSED $_AUTO = analyzer->trace(node);

    // get the incoming expected typing
    auto expected = analyzer->declare(node);

    // get the incoming modifiers to be checked against
    const auto& modifiers = node->modifiers();
    auto exported = modifiers.test(Variable::Flag::EXPORT);
    auto disposable = modifiers.test(Variable::Flag::DISPOSABLE);

    // ensure some conditions about the variable now
    if (exported && disposable) analyzer->report(3000150);

    // attempt declaring on the world now
    auto* entity = analyzer->world()->values().declare(node, expected, analyzer->captures());
    if (entity == nullptr) return analyzer->report(4000403, node->name());  // fail now here

    // update the entity if necessary to do so
    if (disposable) entity->unused(false);

    // handle all the preamble for the node
    return analyzer->preamble(node, entity);
}
