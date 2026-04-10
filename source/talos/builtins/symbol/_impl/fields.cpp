/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Value::Symbol) {
#include "talos/builtins/symbol/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Value::Symbol) = Talos::Member::Storage(name(), {
#include "talos/builtins/symbol/_defines/fields.def"
                                                                      });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Value::Symbol, hash, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Value::Symbol, args.self());
    return Number::Tagged(args.self<Value::Symbol>().hash());
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Value::Symbol)::m_attributes(const Value::Symbol&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
