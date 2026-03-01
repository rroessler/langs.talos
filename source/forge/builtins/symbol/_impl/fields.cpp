/// Forge Modules
#include "forge/member/storage.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Value::Symbol) {
    FORGE_XX_FIELDS_SYMBOL(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
FORGE_BUILTIN_STORAGE(Value::Symbol) = Forge::Member::Storage(name(), { FORGE_XX_FIELDS_SYMBOL(X) });
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_FIELD(Value::Symbol, hash, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Value::Symbol, args.self());
    return Number::Tagged(args.self<Value::Symbol>().hash());
}

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Value::Symbol)::m_attributes(const Value::Symbol&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
