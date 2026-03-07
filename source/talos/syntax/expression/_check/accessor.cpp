/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Accessor, accessor, analyzer) {
    $_UNUSED $_AUTO = analyzer->trace(accessor);
    auto parent = analyzer->check(accessor->parent());

    // if any, the return the any result immediately
    if (parent.type->is<Type::Any>()) return parent;

    // attempt looking up the desired field
    auto field = accessor->field()->name();
    auto entity = parent.type->lookup(field);

    // ensure the entity is actually a valid value
    if (entity.unset()) return analyzer->report(4000200, field, *parent.type);
    if (!entity.opaque()) return analyzer->report(3000200, field);

    // and finally declare the entity as valid now
    return entity.value();
}
