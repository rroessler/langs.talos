/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)
$_FWD(using Self = Type::Protocol, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_FIELDS(Number::Tagged) {
    FORGE_XX_FIELDS_NUMBER(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(Number::Tagged) {
    FORGE_XX_STATICS_NUMBER(X)
};
#undef X

struct FORGE_MM_BUILTIN_ODECL(Number::Tagged, unary, binary);

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Number::Tagged)::typing() { return prototype()->instantiate(); }

FORGE_MM_BUILTIN_FTYPE(Number::Tagged, sign) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, abs) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, ceil) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, floor) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, round) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, trunc) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, clamp) {
    auto minimum = TB::optional(TB::number());
    auto maximum = TB::optional(TB::number());
    auto arguments = TB::arguments(minimum, maximum);
    return { TB::function(TB::number(), arguments) };
}

FORGE_MM_BUILTIN_FTYPE(Number::Tagged, is_nan) { return { TB::function(TB::boolean()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, is_fin) { return { TB::function(TB::boolean()) }; }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, is_inf) { return { TB::function(TB::boolean()) }; }

FORGE_MM_BUILTIN_FTYPE(Number::Tagged, to_precision) { return to_scientific(); }
FORGE_MM_BUILTIN_FTYPE(Number::Tagged, to_scientific, ) {
    auto digits = TB::optional(TB::number());  // prepare digits
    return { TB::function(TB::string(), TB::arguments(digits)) };
}

FORGE_MM_BUILTIN_STYPE(Number::Tagged, parse) {
    auto input = TB::any();  // input type
    auto radix = TB::optional(TB::number());
    auto arguments = TB::arguments(input, radix);
    return { TB::function(TB::number(), arguments) };
}

FORGE_MM_BUILTIN_OTYPE(Number::Tagged, unary, const Self*, Operator::Kind kind) {
    // attempt resolving suitable results now
    switch (kind) {
        case Operator::Kind::INV: $_FALLTHROUGH;
        case Operator::Kind::NEG: return TB::number();
        default: return TB::unset();  // resolve now
    }
}

FORGE_MM_BUILTIN_OTYPE(Number::Tagged, binary, const Self*, Operator::Kind kind, const Type::Erased& right) {
    // if we do not have a secondary "String" typing, then ignore
    if (!right->is<Number::Tagged>()) return TB::unset();

    // attempt resolving a suitable kind to be used now
    switch (kind) {
        case Operator::Kind::ADD:
        case Operator::Kind::SUB: $_FALLTHROUGH;
        case Operator::Kind::MUL: $_FALLTHROUGH;
        case Operator::Kind::DIV: $_FALLTHROUGH;
        case Operator::Kind::MOD: $_FALLTHROUGH;
        case Operator::Kind::POW: $_FALLTHROUGH;

        case Operator::Kind::SHL: $_FALLTHROUGH;
        case Operator::Kind::SHR: $_FALLTHROUGH;
        case Operator::Kind::XOR: $_FALLTHROUGH;
        case Operator::Kind::BOR: $_FALLTHROUGH;
        case Operator::Kind::BAND: return TB::number();

        case Operator::Kind::LT: $_FALLTHROUGH;
        case Operator::Kind::GT: $_FALLTHROUGH;
        case Operator::Kind::LE: $_FALLTHROUGH;
        case Operator::Kind::GE: return TB::boolean();

        // otherwise use the default handler
        default: return TB::unset();
    }
}

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Number::Tagged)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();

    // bind the decision handler for operators
    proto->operators() = Apply::decide;

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ FORGE_XX_FIELDS_NUMBER(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_NUMBER(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
