/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)
$_FWD(using Self = Type::Protocol, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N(const Self*);
struct FORGE_BUILTIN_FIELDS(Iterable::List) {
    FORGE_XX_FIELDS_LIST(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(Iterable::List) {
    FORGE_XX_STATICS_LIST(X)
};
#undef X

struct FORGE_MM_BUILTIN_ODECL(Iterable::List, unary, binary);

//  PROPERTIES  //

/// @brief The core prototype constraint.
static auto g_T = Forge::Builtins::TB::constraint("T", Forge::Builtins::TB::any(), Forge::Builtins::TB::any());

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Iterable::List)::typing() {
    return TB::generic(prototype()->instantiate(), std::vector({ g_T }));
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, size, const Self*) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, empty, const Self*) { return { TB::function(TB::boolean()) }; }

FORGE_MM_BUILTIN_FTYPE(Iterable::List, get, const Self* self) {
    return { TB::function(self->constraints(0), TB::arguments(TB::number())) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, set, const Self* self) {
    return { TB::function(self->constraints(0), TB::arguments(TB::number(), self->constraints(0))) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, front, const Self* self) { return back(self); }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, back, const Self* self) { return { TB::function(self->constraints(0)) }; }

FORGE_MM_BUILTIN_FTYPE(Iterable::List, map, const Self* self) {
    // prepare the constraint
    auto V = TB::constraint("V", TB::any(), TB::any());

    // prepare the incoming values now
    auto index = TB::optional(TB::number());
    auto value = TB::optional(self->constraints(0));

    // prepare the mapping signature
    auto callback = TB::function(V, TB::arguments(value, index));
    auto signature = TB::function(TB::list(V), TB::arguments(callback));

    // and construct the resulting generic now
    return { TB::generic(signature, TB::parameters(V)) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, fold, const Self* self) {
    auto V = TB::constraint("V", TB::any(), TB::any());
    auto callback = TB::function(V, TB::arguments(V, self->constraints(0)));
    auto signature = TB::function(V, TB::arguments(V, callback));
    return { TB::generic(signature, TB::parameters(V)) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, erase, const Self* self) { return slice(self); }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, slice, const Self* self) {
    auto start = TB::optional(TB::number()), end = TB::optional(TB::number());
    return { TB::function(TB::list(self->constraints(0)), TB::arguments(start, end)) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, filter, const Self* self) {
    auto args = TB::arguments(TB::optional(self->constraints(0)));
    auto callback = TB::optional(TB::function(TB::boolean(), args));
    return { TB::function(TB::list(self->constraints(0)), TB::arguments(callback)) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, reverse, const Self* self) {
    return { TB::function(TB::list(self->constraints(0))) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, push_front, const Self* self) { return push_back(self); }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, push_back, const Self* self) {
    return { TB::variadic(TB::number(), TB::arguments(self->constraints(0))) };
}

FORGE_MM_BUILTIN_FTYPE(Iterable::List, pop_front, const Self* self) { return { TB::function(self->constraints(0)) }; }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, pop_back, const Self* self) { return { TB::function(self->constraints(0)) }; }

FORGE_MM_BUILTIN_FTYPE(Iterable::List, first_index_of, const Self* self) { return last_index_of(self); }
FORGE_MM_BUILTIN_FTYPE(Iterable::List, last_index_of, const Self* self) {
    return { TB::function(TB::number(), TB::arguments(self->constraints(0))) };
}

FORGE_MM_BUILTIN_STYPE(Iterable::List, from) {
    auto T = TB::constraint("T");  // prepare the constraints
    auto signature = TB::variadic(TB::list(T), TB::arguments(T));
    return { TB::generic(signature, TB::parameters(T)) };
}

FORGE_MM_BUILTIN_STYPE(Iterable::List, empty) {
    auto T = TB::constraint("T", TB::any(), TB::any());
    auto signature = TB::function(TB::list(T));
    return { TB::generic(signature, TB::parameters(T)) };
}

FORGE_MM_BUILTIN_STYPE(Iterable::List, range) {
    auto index = TB::optional(TB::number());
    auto instance = TB::iterator(TB::number());
    auto args = TB::arguments(index, index, index);
    return { TB::function(instance, args) };
}

FORGE_MM_BUILTIN_STYPE(Iterable::List, filled) {
    auto size = TB::number();
    auto V = TB::constraint("V");
    auto args = TB::arguments(size, V);
    auto signature = TB::function(TB::list(V), args);
    return { TB::generic(signature, TB::parameters(V)) };
}

FORGE_MM_BUILTIN_OTYPE(Iterable::List, unary, const Self* self, Operator::Kind kind) {
    switch (kind) {
        case Operator::Kind::ITER: return self->constraints().at(0);
        default: return TB::unset();  // resolve accordingly
    }
}

FORGE_MM_BUILTIN_OTYPE(Iterable::List, binary, const Self*, Operator::Kind, const Type::Erased&) { return TB::unset(); }

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Iterable::List)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto& fields = proto->fields();

    // prepare the parameter typings now
    proto->constraints() = { g_T };

    // bind the decision handler for operators
    proto->operators() = Apply::decide;

#define X(N, ...) fields.emplace(#N, Field::N);
    FORGE_XX_FIELDS_LIST(X)
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_LIST(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
