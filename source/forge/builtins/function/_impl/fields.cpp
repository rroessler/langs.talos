/// Forge Modules
#include "forge/member/storage.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Function::Dynamic) {
    FORGE_XX_FIELDS_FUNCTION(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
FORGE_BUILTIN_STORAGE(Function::Dynamic) = Forge::Member::Storage(name(), { FORGE_XX_FIELDS_FUNCTION(X) });
#undef X

//  PUBLIC METHODS  //

const Forge::Function::Info* FORGE_BUILTIN_TRAITS(Function::Dynamic)::binder() {
    // prepare the baseline items to be prepared
    static $::Ptr::Shared<Linker::Arena> s_arena = nullptr;
    static $::Ptr::Shared<Function::Info> s_info = nullptr;

    // the expected bytecode to be emplaced
    static std::vector<Bytecode::Instruction> s_bytecode = {
        FORGE_MM_BIR(CLOSURE_PASS, Engine::Accumulator()),
        FORGE_MM_BIR(EXEC_RETURN),  // and return the value
    };

    // if the information is available, then return now
    if (s_info != nullptr) return s_info.get();

    // prepare the shared information to be used
    auto shared = Bytecode::Shared();

    // ensure we define as variadic
    shared.locals = UINT32_MAX;
    shared.adicity = UINT64_MAX;

    // prepare the arena and information now
    s_arena = $::New().shared<Linker::Arena>();
    s_info = $::New().shared<Function::Info>(s_arena.get(), shared);

    // bind the bytecode to call the instance now
    for (const auto& instruction : s_bytecode) s_arena->bytecode.write(instruction.encode());

    // update the buffer before continuing now
    s_info->buffer() = s_arena->bytecode.view();

    // construct the incoming information now
    return s_info.get();
}

FORGE_MM_BUILTIN_FIELD(Function::Dynamic, bind, isolate, args) {
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // ensure size
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return isolate->bind(args.self<Function::Dynamic>(), args[0]);
}

FORGE_MM_BUILTIN_FIELD(Function::Dynamic, arity, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return Number::Tagged(args.self<Function::Dynamic>().arity());
}

FORGE_MM_BUILTIN_FIELD(Function::Dynamic, adicity, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return Number::Tagged(args.self<Function::Dynamic>().adicity());
}

FORGE_MM_BUILTIN_FIELD(Function::Dynamic, receiver, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return args.self<Function::Dynamic>().receiver();  // get now
}

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Function::Dynamic)::m_attributes(
    const Function::Dynamic&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
