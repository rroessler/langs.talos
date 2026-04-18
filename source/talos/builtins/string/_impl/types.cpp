/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)
$_FWD(Talos::Builtins, using Self = Type::Protocol)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(String::Dynamic) {
#include "talos/builtins/string/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(String::Dynamic) {
#include "talos/builtins/string/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

struct TALOS_MM_BUILTIN_ODECL(String::Dynamic, unary, binary);

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(String::Dynamic)::typing() { return prototype()->instantiate(); }

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, size) { return { TB::function(TB::number()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, bytes) { return { TB::function(TB::number()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, empty) { return { TB::function(TB::boolean()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, symbol) { return { TB::function(TB::symbol()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, fmt) { return { TB::variadic(TB::string()) }; }

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, at) {
    Type::Erased returns = TB::maybe(TB::string()), index = TB::number();
    return { TB::function(returns, TB::arguments(index)) };  // construct
}

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, slice) {
    auto start = TB::optional(TB::number());
    auto end = TB::optional(TB::number());
    auto args = TB::arguments(start, end);
    return { TB::function(TB::string(), args) };
}

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, compare) { return { TB::function(TB::number(), TB::arguments(TB::string())) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, contains) {
    Type::Entity search = { TB::string() }, position = TB::optional(TB::number());
    return { TB::function(TB::boolean(), TB::arguments(search, position)) };
}

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, starts_with) { return ends_with(); }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, ends_with) {
    auto arguments = TB::arguments(TB::string());
    return { TB::function(TB::boolean(), arguments) };
}

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, to_lower) { return { TB::function(TB::string()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, to_upper) { return { TB::function(TB::string()) }; }

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, trim_both) { return { TB::function(TB::string()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, trim_leading) { return { TB::function(TB::string()) }; }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, trim_trailing) { return { TB::function(TB::string()) }; }

TALOS_MM_BUILTIN_FTYPE(String::Dynamic, pad_leading) { return pad_trailing(); }
TALOS_MM_BUILTIN_FTYPE(String::Dynamic, pad_trailing) {
    Type::Entity length = { TB::number() }, padding = TB::optional(TB::string());
    return { TB::function(TB::string(), TB::arguments(length, padding)) };
}

TALOS_MM_BUILTIN_STYPE(String::Dynamic, from) { return { TB::function(TB::string(), TB::arguments(TB::any())) }; }
TALOS_MM_BUILTIN_STYPE(String::Dynamic, codepoint) {
    return { TB::function(TB::string(), TB::arguments(TB::number())) };
}

TALOS_MM_BUILTIN_OTYPE(String::Dynamic, unary, const Self*, Operator::Kind kind) {
    switch (kind) {
        case Operator::Kind::ITER: return TB::string();
        default: return TB::unset();  // resolve now
    }
}

TALOS_MM_BUILTIN_OTYPE(String::Dynamic, binary, const Self*, Operator::Kind kind, const Type::Erased& right) {
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

void TALOS_BUILTIN_TRAITS(String::Dynamic)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto& fields = proto->fields();
    auto& statics = proto->statics();

    // bind the decision handler for operators
    proto->operators() = Apply::decide;

#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/string/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/string/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
