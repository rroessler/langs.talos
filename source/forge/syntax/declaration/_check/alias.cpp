/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Alias, alias, analyzer) {
    // prepare a transform for resolving our target now
    auto transform = Type::Builder::transform();

    // prepare the details about the alias now
    auto name = alias->name();
    auto location = alias->traits()->location();

    // pre-declare the entity as necessary
    auto* entity = analyzer->world()->types().declare(name, transform, location);
    if (entity == nullptr) return analyzer->report(alias, 4000402, name);  // failure

    // prepare a current scoping to be used now
    $_UNUSED $_AUTO = analyzer->scope();

    // get the current generics to be used now
    auto constraints = analyzer->check(alias->generics());

    auto hint = analyzer->check(alias->hint()).type;  // resolve the typing
    if (hint->is<Type::Protocol>()) hint->as<Type::Protocol>()->name() = name;
    if (constraints.size()) hint = Type::Builder::generic(hint, constraints);

    // update the entity to contain this hint now
    transform->target() = hint;

    // otherwise update the exported flag if necessary
    auto exported = alias->modifiers().test(Variable::Flag::EXPORT);
    if (exported) entity->modifiers().set(Variable::Flag::EXPORT);

    // return a passable result now
    return analyzer->passable(transform);
}
