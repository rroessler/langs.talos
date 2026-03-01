/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)
$_FWD(using Self = Type::Protocol, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N(const Self*);
struct FORGE_BUILTIN_FIELDS(Async::Future) {
    FORGE_XX_FIELDS_FUTURE(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(Async::Future) {
    FORGE_XX_STATICS_FUTURE(X)
};
#undef X

//  PROPERTIES  //

/// @brief The core prototype constraint.
static auto g_T = Forge::Builtins::TB::constraint("T", Forge::Builtins::TB::any(), Forge::Builtins::TB::any());

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Async::Future)::typing() {
    return TB::generic(prototype()->instantiate(), std::vector({ g_T }));
}

FORGE_MM_BUILTIN_FTYPE(Async::Future, then, const Self* self) {
    // prepare a value constraint to convert to
    auto V = TB::constraint("V");

    // prepare a future-like value now
    auto returns = TB::future(V);
    auto either = TB::merge(V, returns);

    // prepare an incoming callback now
    auto value = TB::optional(self->constraints(0));
    auto callback = TB::function(either, TB::arguments(value));

    // and now construct the resulting signature
    auto signature = TB::function(returns, TB::arguments(callback));
    return { TB::generic(signature, TB::parameters(V)) };  // bind
}

FORGE_MM_BUILTIN_FTYPE(Async::Future, fails, const Self* self) {
    // prepare the incoming return-typing
    auto value = self->constraints(0);
    auto returns = TB::future(value);
    auto either = TB::merge(value, returns);

    // prepare the incoming callback now
    auto exception = TB::optional(TB::any());
    auto callback = TB::function(either, TB::arguments(exception));

    // and construct the resulting signature to be used
    return { TB::function(returns, TB::arguments(callback)) };
}

FORGE_MM_BUILTIN_FTYPE(Async::Future, await, const Self* self) { return { TB::function(self->constraints(0)) }; }
FORGE_MM_BUILTIN_FTYPE(Async::Future, state, const Self*) { return { TB::function(TB::number()) }; }

FORGE_MM_BUILTIN_STYPE(Async::Future, async) {
    auto F = TB::constraint("F", TB::variadic());
    auto signature = TB::invocation(F, true);
    return { TB::generic(signature, TB::parameters(F)) };
}

FORGE_MM_BUILTIN_STYPE(Async::Future, delay) {
    auto duration = TB::optional(TB::number()), callback = TB::optional(TB::function(TB::none()));
    return { TB::function(TB::future(TB::none()), TB::arguments(duration, callback)) };
}

FORGE_MM_BUILTIN_STYPE(Async::Future, resolve) {
    auto T = TB::constraint("T");  // prepare the type-constraint
    auto signature = TB::function(TB::future(T), TB::arguments(T));
    return { TB::generic(signature, TB::parameters(T)) };  // bind
}

FORGE_MM_BUILTIN_STYPE(Async::Future, reject) {
    auto T = TB::constraint("T", TB::any(), TB::any());  // prepare constraint
    auto signature = TB::function(TB::future(T), TB::arguments(TB::any()));
    return { TB::generic(signature, TB::parameters(T)) };  // bind
}

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Async::Future)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto& fields = proto->fields();

    // prepare the parameter typings now
    proto->constraints() = { g_T };

#define X(N, ...) fields.emplace(#N, Field::N);
    FORGE_XX_FIELDS_FUTURE(X)
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_FUTURE(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
