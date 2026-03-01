/// Forge Modules
#include "forge/member/factory.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Builtins::Custom::Debug) {
    FORGE_XX_FIELDS_DEBUG(X)
};
#undef X

//  PUBLIC METHODS  //

#define X(N, ...)                                                                \
    FORGE_MM_BUILTIN_FIELD(Builtins::Custom::Debug, N, , arguments) {            \
        return $::IO::N("{0}", fmt::join(arguments.span(), " ")), Value::Void(); \
    }

FORGE_XX_FIELDS_DEBUG(X)
#undef X

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Builtins::Custom::Debug)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Instance>();

// assign the necessary fields now
#define X(N, ...) self.fields().emplace(#N, Member::Factory::native(isolate, Field::N, name(), #N));
    FORGE_XX_FIELDS_DEBUG(X)
#undef X

    // and return the resulting instance
    return self;
}
