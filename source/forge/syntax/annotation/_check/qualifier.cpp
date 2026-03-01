/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Qualifier, node, analyzer) {
    // get the underlying segments
    const auto& segments = node->segments();

    // ensure that we actually have some segments to begin with
    $_ASSERT(!segments.empty(), "Qualifier segments cannot be empty");

    // get the current identifier to be used
    auto* identifier = segments.front();
    auto name = identifier->name();
    auto chain = $::String::Buffer(name);

    auto [entity, depth] = analyzer->world()->lookup(name);  // get the entity
    if (entity == nullptr) return analyzer->report(identifier, 4000300, chain);

    // update the entity reference flag now and mark the first identifier
    entity->unused(false), analyzer->mark(identifier, entity, depth);

    // construct the iterator element now
    auto segment = *entity;

    // iterate through the available fields now
    for (size_t ii = 1; ii < segments.size(); ++ii) {
        // ensure the current entity is opaque and can be used
        if (!segment.opaque()) return analyzer->report(identifier, 3000200, chain);

        identifier = segments.at(ii);  // update our details
        segment = segment.value()->lookup(identifier->name());

        // fail immediately if there is no valid reference
        if (segment.unset()) return analyzer->report(identifier, 4000200, chain, name);

        // post-update the current chain to be used
        chain += "." + $::String::Buffer(identifier->name());
    }

    // ensure the final segment we have is transient before inferring the type
    if (!entity->transient()) return analyzer->report(identifier, 3000201, chain);

    $_UNUSED $_AUTO = analyzer->trace(node);  // ensure we trace errors here as well
    return analyzer->passable(analyzer->instantiate(segment.type(), node->types()));
}
