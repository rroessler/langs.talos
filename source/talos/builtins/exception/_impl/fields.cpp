/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Object::Exception) {
#include "talos/builtins/exception/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Object::Exception) = Talos::Member::Storage(name(), {
#include "talos/builtins/exception/_defines/fields.def"
                                                                          });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Object::Exception, name, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self());
    return args.self<Object::Exception>().name();  // get the name
}

TALOS_MM_BUILTIN_FIELD(Object::Exception, message, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self());
    return args.self<Object::Exception>().message();  // get the name
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Object::Exception)::m_attributes(
    const Object::Exception&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
