/// Talos Modules
#include "talos/type/visitor.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PUBLIC METHODS  //

TALOS_MM_CHECK_NODE(Class, node, analyzer) {
    // get the baseline location of the node
    auto location = node->traits()->location();

    // pre-declare the entity instance now
    auto overlap = !analyzer->world()->declare(node->name(), location);
    if (overlap) return analyzer->report(4000406, node->name());

    // ensure that the signature is valid
    auto constructor = analyzer->check(node->constructor()).type;
    if (constructor->is<Type::Any>()) return constructor;

    // attempt checking the baseline prototype details
    auto shape = analyzer->shapes()->assign(node);

    // construct the underlying class prototype now
    auto proto = Type::Builder::prototype(node->name(), shape);

    // and construct a baseline instance to be used now
    auto instance = proto->instantiate();

    // set some of the constructor details to be used
    auto generic = Type::Builder::resolve<Type::Generic>(constructor);

    // update the necessary components to be used now
    auto constraints = generic ? generic->parameters() : Type::Template();
    proto->constraints() = $::Ranges::To<Type::Erased>(constraints);

    // update the underlying constructor function to be used
    proto->constructor() = [constructor](const Type::Prototype* proto) -> Type::Erased {
        auto returns = const_cast<Type::Prototype*>(proto)->instantiate();
        auto callable = Type::Builder::resolve<Type::Callable>(constructor);
        return Type::Builder::function(returns, callable->parameters());
    };

    // resolve the entity and it's context now
    auto* entity = analyzer->world()->lookup(node->name()).first;

    // can safely update the underlying entity details now
    entity->context() = analyzer->captures().declare(node);
    entity->value() = Type::Builder::generic(proto, constraints);
    entity->type() = Type::Builder::generic(instance, constraints);

    // prepare the current trace location
    $_UNUSED $_AUTO = analyzer->trace(node);

    // prepare the incoming world to be used for scoping
    auto world = analyzer->scope(node->constructor(), proto->callable());

    // attempt resolving the incoming extension instance
    auto extends = analyzer->check(node->extends(), Type::Builder::none()).type;
    if (extends == proto) analyzer->report(node, 3001000, node->name());  // do not allow self-references
    else if (auto super = Type::Builder::resolve<Type::Prototype>(extends)) proto->super() = extends;
    else if (!extends->is<Type::None>()) analyzer->report(node->extends(), 3001001, node->name(), *extends);

    // prepare the "self" value to be used now as well
    world->values().declare("self", instance)->unused(false);

    // start attempting to declare all the available fields
    for (const auto& field : node->fields()) {
        /// TODO: attempt checking the incoming field
        auto member = analyzer->check(field).type;
    }

    // attempt checking all the available fields now for use
    return analyzer->passable(entity->value());
}
