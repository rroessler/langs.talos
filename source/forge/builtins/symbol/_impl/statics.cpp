/// Forge Modules
#include "forge/member/factory.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(Value::Symbol) {
    FORGE_XX_STATICS_SYMBOL(X)
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(Value::Symbol, from, isolate, args) {
    // ensure the correct number of arguments given
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);

    // get the value to question and validate as needed
    auto value = args.at(0);

    // cast depending on the type of the value
    if (value.is<String::Dynamic>()) return value.as<String::Dynamic>().symbol();

    // otherwise cast using the pointer directly
    return Value::Symbol(value.traits());
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Value::Symbol)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_SYMBOL(X)
#undef X

    // and return the resulting instance
    return self;
}
