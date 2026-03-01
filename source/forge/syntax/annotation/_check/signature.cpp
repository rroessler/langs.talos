/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PUBLIC METHODS  //

FORGE_MM_CHECK_NODE(Parameters, node, analyzer) {
    // prepare the output entities to be used now
    auto entities = std::vector<Type::Entity>();
    entities.reserve(node->list().size());

    // prepare the parameters view to be used
    for (const auto& parameter : node->list()) {
        // prepare the parameter trace to be used
        $_UNUSED $_AUTO = analyzer->trace(parameter);

        // prepare the underlying entity to be updated now
        auto& entity = entities.emplace_back(Type::Entity());

        entity.modifiers() = parameter->modifiers();  // bind the initial modifiers and type
        entity.value() = analyzer->check(parameter->hint(), Type::Builder::any()).type;
        parameter->traits()->type() = entity.value();  // ensure we cache the parameter type

        // ignore if there is not given initializer at all
        if (parameter->initializer() == nullptr) continue;

        // get the initializer value now
        auto initializer = analyzer->check(parameter->initializer()).type;

        // update the modifiers to now include optionality
        entity.modifiers().set(Variable::Flag::OPTIONAL);

        // handle validating the required optionality now
        if (parameter->optional() && initializer->is<Type::None>()) continue;
        else if (entity.value()->unify(initializer)) continue;

        // invalidate the initializer here as needed
        analyzer->report(3000300, *initializer, *entity.value());
    }

    // and construct the resulting signature to be used
    if (node->spread()) return { Type::Builder::variadic(Type::Builder::unset(), entities) };
    else return { Type::Builder::function(Type::Builder::unset(), entities) };  // non-variadic
}

FORGE_MM_CHECK_NODE(Constructor, node, analyzer) {
    // get the current generics to be used now
    auto constraints = analyzer->check(node->generics());

    // attempt resolving the underlying parameters
    auto callable = analyzer->check(node->parameters()).type->as<Type::Callable>();

    // and construct the return typing based on the total constraints
    if (constraints.empty()) return analyzer->passable(callable);
    else return { Type::Builder::generic(callable, constraints) };
}

FORGE_MM_CHECK_NODE(Signature, node, analyzer) {
    // force an immediate scoping to occur now
    $_UNUSED $_AUTO = analyzer->scope();
    $_UNUSED $_AUTO = analyzer->trace(node);

    // check the underlying signature typing first
    auto signature = analyzer->check(node->prototype()).type;

    auto* parameters = node->prototype()->parameters();  // update retval
    auto callable = parameters->traits()->type()->as<Type::Callable>();
    callable->returns() = analyzer->check(node->returns()).type;

    // and return the resulting signature typing as necessary
    return { signature };
}
