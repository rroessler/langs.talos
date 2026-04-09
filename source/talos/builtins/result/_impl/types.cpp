/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)
$_FWD(Talos::Builtins, using Self = Type::Protocol)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Type::Entity N(const Self*);
struct TALOS_BUILTIN_FIELDS(Monad::Result) {
#include "talos/builtins/result/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Monad::Result) {
#include "talos/builtins/result/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

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
    auto& statics = proto->statics();

    // set the underlying constraints
    proto->constraints() = { g_T, g_E };

#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N);
#include "talos/builtins/result/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/result/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
