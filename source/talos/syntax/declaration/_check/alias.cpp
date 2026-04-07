/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Alias, node, analyzer) {
    // prepare a transform for resolving our target now
    auto transform = Type::Builder::transform();

    // prepare the details about the alias now
    auto name = node->name();
    auto location = node->traits()->location();

    // pre-declare the entity as necessary
    auto* entity = analyzer->world()->types().declare(name, transform, location);
    if (entity == nullptr) return analyzer->report(node, 4000402, name);  // failure

    // prepare a current scoping to be used now
    $_UNUSED $_AUTO = analyzer->scope();

    // get the current generics to be used now
    auto constraints = analyzer->check(node->generics());

    auto hint = analyzer->check(node->hint()).type;  // resolve the typing
    if (hint->is<Type::Protocol>()) hint->as<Type::Protocol>()->name() = name;

    // update the entity to contain this hint now
    transform->target() = Type::Builder::generic(hint, constraints);

    // otherwise update the exported flag if necessary
    auto exported = node->modifiers().test(Variable::Flag::EXPORT);
    if (exported) entity->modifiers().set(Variable::Flag::EXPORT);

    // return a passable result now
    return analyzer->passable(transform);
}
