/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)
$_FWD(using Self = Type::Protocol, Talos::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N(const Self*);
struct TALOS_BUILTIN_FIELDS(Monad::Result) {
    TALOS_XX_FIELDS_RESULT(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Monad::Result) {
    TALOS_XX_STATICS_RESULT(X)
};
#undef X

//  PROPERTIES  //

/// @brief The core prototype constraint.
static auto g_T = Talos::Builtins::TB::constraint("T", Talos::Builtins::TB::any(), Talos::Builtins::TB::any());
static auto g_E = Talos::Builtins::TB::constraint("E", Talos::Builtins::TB::any(), Talos::Builtins::TB::any());

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Monad::Result)::typing() {
    return TB::generic(prototype()->instantiate(), std::vector({ g_T, g_E }));
}

TALOS_MM_BUILTIN_FTYPE(Monad::Result, is_okay, const Self*) { return { TB::function(TB::boolean()) }; }
TALOS_MM_BUILTIN_FTYPE(Monad::Result, is_error, const Self*) { return { TB::function(TB::boolean()) }; }

TALOS_MM_BUILTIN_FTYPE(Monad::Result, unwrap_okay, const Self* self) {
    auto value = self->constraints(0);
    auto message = TB::optional(TB::string());
    auto args = TB::arguments(message);
    return { TB::function(value, args) };
}

TALOS_MM_BUILTIN_FTYPE(Monad::Result, unwrap_error, const Self* self) {
    auto error = self->constraints(0);
    auto message = TB::optional(TB::string());
    auto args = TB::arguments(message);
    return { TB::function(error, args) };
}

TALOS_MM_BUILTIN_STYPE(Monad::Result, wrap) {
    auto T = TB::constraint("T", TB::future(TB::any()));
    auto result = TB::result(TB::awaited(T), TB::exception());
    auto signature = TB::function(result, TB::arguments(T));
    return { TB::generic(signature, TB::parameters(T)) };
}

TALOS_MM_BUILTIN_STYPE(Monad::Result, okay) {
    // prepare the constraints
    auto T = TB::constraint("T", TB::any(), TB::any());
    auto E = TB::constraint("E", TB::any(), TB::any());

    // prepare the result instance now
    auto result = TB::result(T, E);
    auto args = TB::arguments(T);
    auto signature = TB::function(result, args);

    // and construct the factory generic
    return { TB::generic(signature, TB::parameters(T, E)) };
}

TALOS_MM_BUILTIN_STYPE(Monad::Result, error) {
    // prepare the constraints
    auto T = TB::constraint("T", TB::any(), TB::any());
    auto E = TB::constraint("E", TB::any(), TB::any());

    // prepare the result instance now
    auto result = TB::result(T, E);
    auto args = TB::arguments(E);
    auto signature = TB::function(result, args);

    // and construct the factory generic
    return { TB::generic(signature, TB::parameters(T, E)) };
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Monad::Result)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto& fields = proto->fields();

    // set the underlying constraints
    proto->constraints() = { g_T, g_E };

#define X(N, ...) fields.emplace(#N, Field::N);
    TALOS_XX_FIELDS_RESULT(X)
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = $::Record<Type::Entity>({ TALOS_XX_STATICS_RESULT(X) });
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
