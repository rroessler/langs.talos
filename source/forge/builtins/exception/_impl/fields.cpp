/// Forge Modules
#include "forge/member/storage.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Object::Exception) {
    FORGE_XX_FIELDS_EXCEPTION(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
FORGE_BUILTIN_STORAGE(Object::Exception) = Forge::Member::Storage(name(), { FORGE_XX_FIELDS_EXCEPTION(X) });
#undef X

//  PUBLIC METHODS  //

#define X(N, ...)                                                        \
    FORGE_MM_BUILTIN_FIELD(Object::Exception, N, isolate, args) {        \
        FORGE_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self()); \
        return args.self<Object::Exception>().N();                       \
    }

FORGE_XX_FIELDS_EXCEPTION(X)
#undef X

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Object::Exception)::m_attributes(
    const Object::Exception&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
