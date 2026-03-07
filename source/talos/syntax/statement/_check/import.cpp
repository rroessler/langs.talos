/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Import, node, analyzer) {
    auto* module = analyzer->import(node->path(), node->traits()->location());
    $_ASSERT(module, "Expected module to be a non-nullptr");  // ensure exists

    // prepare some details about the module
    auto* world = analyzer->world();
    auto exports = module->exports();
    auto dynamic = module->dynamic();
    auto wildcard = node->wildcard();
    auto& captures = analyzer->captures();

    // prepare the underlying dynamic type to be used
    auto monotype = dynamic ? module->monotype() : Type::Builder::interface(node->path(), exports);

    // resolve the resource patterns to be used now
    for (const auto* pattern : node->patterns()) {
        // trace the pattern that we are resolving now
        $_UNUSED $_AUTO = analyzer->trace(pattern);

        // prepare some details about the pattern
        auto name = pattern->name();
        auto location = pattern->traits()->location();

        // ensure we get the underlying entity to be used now
        auto exists = wildcard ? false : exports.contains(name);
        auto entity = exists ? exports.at(name) : Type::Entity();

        // update the conditional details for the entity firstly
        if (node->exported()) entity.modifiers().set(Variable::Flag::EXPORT);
        else entity.modifiers().clear(Variable::Flag::EXPORT);

        // always update the entity details to be used
        entity.unused(!entity.exported());
        entity.context() = captures.declare(pattern);

        if (wildcard) entity.value() = monotype;  // resolve the entity value
        else if (!exists && dynamic) exists = true, entity.value() = monotype;

        // declare an error for items that cannot be exported
        if (!exists && !wildcard) analyzer->report(8000300, name);
        else if (world->declare(name, entity, location)) continue;
        else analyzer->report(4000403, name);  // failed to declare
    }

    // always declare as passable (regardless) of errors
    return analyzer->passable(monotype);
}
