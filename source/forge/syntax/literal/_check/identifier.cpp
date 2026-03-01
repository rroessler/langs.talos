/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Identifier, identifier, analyzer) {
    // get the underlying identifier name
    auto name = identifier->name();

    // prepare tracing for the identifier now
    $_UNUSED $_AUTO = analyzer->trace(identifier);

    // attempt getting a type for the current identifier
    auto [entity, depth] = analyzer->world()->lookup(name);

    // declare an error if the variable does not exist or not a value
    if (entity == nullptr) return analyzer->report(4000301, name);
    if (!entity->opaque()) return analyzer->report(3000200, name);

    // update the current entity as used and return the value
    return analyzer->mark(identifier, entity, depth), entity->value();
}
