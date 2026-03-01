/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)
$_FWD(using Self = Type::Protocol, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_FIELDS(String::Dynamic) {
    FORGE_XX_FIELDS_STRING(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(String::Dynamic) {
    FORGE_XX_STATICS_STRING(X)
};
#undef X

struct FORGE_MM_BUILTIN_ODECL(String::Dynamic, unary, binary);

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(String::Dynamic)::typing() { return prototype()->instantiate(); }

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, hash) { return { TB::function(TB::symbol()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, size) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, bytes) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, empty) { return { TB::function(TB::boolean()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, fmt) { return { TB::variadic(TB::string()) }; }

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, at) {
    Type::Erased returns = TB::maybe(TB::string()), index = TB::number();
    return { TB::function(returns, TB::arguments(index)) };  // construct
}

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, slice) {
    auto start = TB::optional(TB::number());
    auto end = TB::optional(TB::number());
    auto args = TB::arguments(start, end);
    return { TB::function(TB::string(), args) };
}

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, compare) { return { TB::function(TB::number(), TB::arguments(TB::string())) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, contains) {
    Type::Entity search = { TB::string() }, position = TB::optional(TB::number());
    return { TB::function(TB::boolean(), TB::arguments(search, position)) };
}

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, starts_with) { return ends_with(); }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, ends_with) {
    auto arguments = TB::arguments(TB::string());
    return { TB::function(TB::boolean(), arguments) };
}

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, to_lower) { return { TB::function(TB::string()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, to_upper) { return { TB::function(TB::string()) }; }

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, trim_both) { return { TB::function(TB::string()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, trim_leading) { return { TB::function(TB::string()) }; }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, trim_trailing) { return { TB::function(TB::string()) }; }

FORGE_MM_BUILTIN_FTYPE(String::Dynamic, pad_leading) { return pad_trailing(); }
FORGE_MM_BUILTIN_FTYPE(String::Dynamic, pad_trailing) {
    Type::Entity length = { TB::number() }, padding = TB::optional(TB::string());
    return { TB::function(TB::string(), TB::arguments(length, padding)) };
}

FORGE_MM_BUILTIN_STYPE(String::Dynamic, from) { return { TB::function(TB::string(), TB::arguments(TB::any())) }; }
FORGE_MM_BUILTIN_STYPE(String::Dynamic, codepoint) {
    return { TB::function(TB::string(), TB::arguments(TB::number())) };
}

FORGE_MM_BUILTIN_OTYPE(String::Dynamic, unary, const Self*, Operator::Kind kind) {
    switch (kind) {
        case Operator::Kind::ITER: return TB::string();
        default: return TB::unset();  // resolve now
    }
}

FORGE_MM_BUILTIN_OTYPE(String::Dynamic, binary, const Self*, Operator::Kind kind, const Type::Erased& right) {
    // if we do not have a secondary "String" typing, then ignore
    if (!right->is<String::Dynamic>()) return TB::unset();

    // attempt matching as necessary now
    switch (kind) {
        // check against the basic addition handler
        case Operator::Kind::ADD: return TB::string();

        // allow checking against comparison handlers
        case Operator::Kind::LT: $_FALLTHROUGH;
        case Operator::Kind::GT: $_FALLTHROUGH;
        case Operator::Kind::LE: $_FALLTHROUGH;
        case Operator::Kind::GE: return TB::boolean();

        // fallback to the default handler
        default: return TB::unset();
    }
}

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(String::Dynamic)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();

    // bind the decision handler for operators
    proto->operators() = Apply::decide;

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ FORGE_XX_FIELDS_STRING(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_STRING(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
