/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Namespace, node, analyzer) {
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

    // attempt declaring our entity to be used now
    auto* entity = analyzer->world()->values().declare(analyzer->sanity(node), result.type);
    return entity == nullptr ? analyzer->report(4000403, node->name()) : std::move(result);
}
