/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)
$_FWD(Talos::Builtins, using Self = Type::Protocol)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N(const Self*);
struct TALOS_BUILTIN_FIELDS(Iterable::Iterator) {
    TALOS_XX_FIELDS_ITERATOR(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Iterable::Iterator) {
    TALOS_XX_STATICS_ITERATOR(X)
};
#undef X

struct TALOS_MM_BUILTIN_ODECL(Iterable::Iterator, unary, binary);

//  PROPERTIES  //

/// @brief The core prototype constraint.
static auto g_T = Talos::Builtins::TB::constraint("T", Talos::Builtins::TB::any(), Talos::Builtins::TB::any());

/// @brief Available generator name.
static constexpr auto g_generator = "Generator";

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Iterable::Iterator)::typing() {
    return TB::generic(prototype()->instantiate(), std::vector({ g_T }));
}

$::Ptr::Shared<Talos::Type::Generic> TALOS_BUILTIN_TRAITS(Iterable::Iterator)::generator() {
    // prepare the baseline typing to output
    static $::Ptr::Shared<Type::Generic> s_generator = nullptr;

    // stop early if already constructed here
    if (s_generator != nullptr) return s_generator;

    // prepare the context parameter to be used
    auto V = TB::constraint("V", TB::any(), TB::any());

    // prepare the yield handler to be used
    auto yield = TB::optional(TB::function(TB::none(), TB::arguments(V)));

    // prepare the arguments and signature to be used
    auto arguments = TB::arguments(TB::number(), yield);
    auto signature = TB::function(TB::boolean(), arguments);

    // return the resulting context typing now
    return s_generator = $::New().shared<Type::Generic>(signature, TB::parameters(V));
}

TALOS_MM_BUILTIN_FTYPE(Iterable::Iterator, done, const Self*) { return { TB::function(TB::boolean()) }; }
TALOS_MM_BUILTIN_FTYPE(Iterable::Iterator, next, const Self*) { return { TB::function(TB::boolean()) }; }
TALOS_MM_BUILTIN_FTYPE(Iterable::Iterator, index, const Self*) { return { TB::function(TB::number()) }; }

TALOS_MM_BUILTIN_STYPE(Iterable::Iterator, empty) {
    auto T = TB::constraint("T", TB::any(), TB::any());
    auto signature = TB::function(TB::iterator(T));
    return { TB::generic(signature, TB::parameters(T)) };
}

TALOS_MM_BUILTIN_STYPE(Iterable::Iterator, from) {
    // prepare the constraints to be used
    auto T = TB::constraint("T");

    // construct the signature that resolves a suitable iterable
    auto signature = TB::function(TB::iterable(T), TB::arguments(T));

    // allow binding the generics required for this instance
    return { TB::generic(signature, TB::parameters(T)) };
}

TALOS_MM_BUILTIN_STYPE(Iterable::Iterator, dynamic) {
    // prepare the constraints to be used
    auto T = TB::constraint("T", TB::any(), TB::any());

    // prepare the signature to be used for the generator
    auto arguments = TB::arguments(generator()->instantiate({ T }));
    auto signature = TB::function(TB::iterator(T), arguments);

    // allow binding the generics required for this instance
    return { TB::generic(signature, TB::parameters(T)) };
}

TALOS_MM_BUILTIN_OTYPE(Iterable::Iterator, unary, const Self* self, Operator::Kind kind) {
    switch (kind) {
        case Operator::Kind::ITER: return self->constraints().at(0);
        default: return TB::unset();  // resolve accordingly
    }
}

TALOS_MM_BUILTIN_OTYPE(Iterable::Iterator, binary, const Self*, Operator::Kind, const Type::Erased&) {
    return TB::unset();
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Iterable::Iterator)::m_typedefs(Type::World* globals) {
    // prepare the underlying prototype to be used
    auto proto = prototype();
    auto& fields = proto->fields();

    // prepare the parameter typings now
    proto->constraints() = { g_T };

    // bind the decision handler for operators
    proto->operators() = Apply::decide;

#define X(N, ...) fields.emplace(#N, Field::N);
    TALOS_XX_FIELDS_ITERATOR(X)
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { TALOS_XX_STATICS_ITERATOR(X) };
#undef X

    // bind the necessary properties now for use
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);

    // bind the context to it's own generator typing
    globals->types().declare(g_generator, generator());
}
