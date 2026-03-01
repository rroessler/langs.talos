/// Forge Modules
#include "forge/type/visitor.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

/// Forward Declarations
$_FWD(Erased returns(const Syntax::Lambda*, const Erased&), Forge::Type::Dispatch)
$_FWD(void lambda(Analyzer*, const Syntax::Lambda*, const Erased&), Forge::Type::Dispatch)

//  PUBLIC METHODS  //

Forge::Type::Erased Forge::Type::Dispatch::returns(const Syntax::Lambda* lambda, const Erased& returns) {
    // return the original return value if valid
    if (!returns->is<Unset>()) return returns;

    // otherwise check if using an arrow function
    auto arrow = !lambda->body()->is<Syntax::Block>();

    // resolve as necesasry now
    if (arrow) return Builder::any();
    else return Builder::none();
}

void Forge::Type::Dispatch::lambda(Analyzer* analyzer, const Syntax::Lambda* self, const Erased& signature) {
    // scope a new world to be used now
    auto world = analyzer->scope();
    auto& captures = analyzer->captures();

    // update the current world callee
    world->callee() = signature;

    // prepare the current trace location
    $_UNUSED $_AUTO = analyzer->trace(self);

    // get the details about the type now
    auto generic = Builder::resolve<Generic>(signature);
    auto callable = Builder::resolve<Callable>(signature);

    auto parameters = callable->parameters();  // get the base details now
    auto spread = callable->packed() ? Type::Builder::list(parameters.back().value()) : nullptr;

    // pre-define any generic type parameters now
    for (const auto& constraint : generic ? generic->parameters() : Builder::parameters()) {
        auto entity = world->types().declare(constraint->name(), constraint);
        if (entity == nullptr) analyzer->report(4000400, constraint->name());
    }

    // resolve all the necessary arguments now
    for (const auto& [ii, parameter] : $::Each(self->parameters())) {
        // attempt getting the current details to be used
        auto optional = parameter->optional();
        auto packed = parameter == self->signature()->spread();

        // prepare the incoming type to be used now
        auto type = packed ? spread : parameters.at(ii).value();

        // stop on invalid parameter types
        if (type == nullptr) break;

        // if we are in spread-mode, then change to an array
        if (optional) type = Builder::maybe(type);

        auto* entity = world->values().declare(parameter, type, captures);  // declare
        if (entity == nullptr) analyzer->report(parameter, 4000401, parameter->name());
    }

    // attempt resolving the body now as normal
    auto result = analyzer->check(self->body());

    // push the return-typing as the current trace value
    $_UNUSED $_AUTO = analyzer->trace(self->signature()->returns());

    // ensure we use the implicit handler when necessary
    auto returns = callable->returns();

    // start determining the current return-typing
    auto arrow = !self->body()->is<Syntax::Block>();

    // ensure the flow is unreachable and non-arrow
    if (!arrow && result.flow->unreachable()) return;

    // attempt running a unification here as necessary
    if (!returns->unify(result.type)) {
        if (returns->lattice().bottom()) analyzer->report(3000901);
        else if (!arrow && !returns->is<None>()) analyzer->report(3000902);
        else analyzer->report(self->body(), 3000300, *result.type, *returns);
    }
}

FORGE_MM_CHECK_NODE(Lambda, lambda, analyzer) {
    // immediately ensure that the signature is valid
    auto result = analyzer->check(lambda->signature());

    // return early when necessary to do so here
    if (result.type->is<Type::Any>()) return result;

    // get the return-typing of the result
    auto callable = Type::Builder::resolve<Type::Callable>(result.type);
    callable->returns() = Type::Dispatch::returns(lambda, callable->returns());

    // prepare the deferred check handler
    Type::Deferrer check = [lambda, type = result.type](auto* _) mutable { Type::Dispatch::lambda(_, lambda, type); };

    // push the incoming instance onto main checker now
    return analyzer->defer(std::move(result), std::move(check));
}
