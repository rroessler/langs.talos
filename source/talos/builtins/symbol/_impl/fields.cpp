/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Value::Symbol) {
    TALOS_XX_FIELDS_SYMBOL(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Value::Symbol) = Talos::Member::Storage(name(), { TALOS_XX_FIELDS_SYMBOL(X) });
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Value::Symbol, hash, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Value::Symbol, args.self());
    return Number::Tagged(args.self<Value::Symbol>().hash());
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Value::Symbol)::m_attributes(const Value::Symbol&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
