/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Namespace, node, analyzer) {
    // prepare an initial result to be used
    auto result = analyzer->unreachable();

    // prepare the trace to record back to this instance
    $_UNUSED $_AUTO = analyzer->trace(node);

    // scope the incoming namespace now
    $_PP_SCOPE() {
        auto world = analyzer->scope();  // scope
        auto fields = $::Record<Type::Entity>();

        // prepare the result to be used
        result = analyzer->check(node->block()->statements());

        // iterate over the available fields in the world
        for (const auto& [name, entity] : world->entities()) {
            if (entity.exported()) fields.emplace(name, entity);
        }

        // update the results typing now
        result.type = Type::Builder::interface(node->name(), fields);
    }

    auto* entity = analyzer->world()->values().declare(node, result.type, analyzer->captures());
    return entity ? std::move(result) : analyzer->report(4000403, node->name());  // failed to declare
}
