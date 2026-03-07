/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Object::Exception) {
    TALOS_XX_FIELDS_EXCEPTION(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Object::Exception) = Talos::Member::Storage(name(), { TALOS_XX_FIELDS_EXCEPTION(X) });
#undef X

//  PUBLIC METHODS  //

#define X(N, ...)                                                        \
    TALOS_MM_BUILTIN_FIELD(Object::Exception, N, isolate, args) {        \
        TALOS_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self()); \
        return args.self<Object::Exception>().N();                       \
    }

TALOS_XX_FIELDS_EXCEPTION(X)
#undef X

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Object::Exception)::m_attributes(
    const Object::Exception&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
