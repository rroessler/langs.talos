/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Function::Dynamic) {
#include "talos/builtins/function/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Function::Dynamic) = Talos::Member::Storage(name(), {
#include "talos/builtins/function/_defines/fields.def"
                                                                          });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

const Talos::Function::Info* TALOS_BUILTIN_TRAITS(Function::Dynamic)::binder() {
    // prepare the baseline items to be prepared
    static const Function::Info* s_info = nullptr;
    static $::URI::Buffer s_resource = $::URI::Evaluate("Function.bind()");
    static $::Ptr::Shared<Linker::Arena> s_arena = $::New().shared<Linker::Arena>();

    // the expected bytecode to be emplaced
    static std::vector<Bytecode::Instruction> s_bytecode = {
        TALOS_MM_BIR(CLOSURE_PASS, Engine::Accumulator()),
        TALOS_MM_BIR(EXEC_RETURN),  // and return the value
    };

    // if the information is available, then return now
    if (s_info != nullptr) return s_info;

    // prepare the shared information to be used
    auto shared = Bytecode::Shared();

    // ensure we define as variadic
    shared.locals = UINT32_MAX;
    shared.adicity = UINT64_MAX;

    // prepare the arena details to be used now
    s_arena->resource = s_resource;

    // construct a new set of function information to be used now
    auto info = $::New().unique<Function::Info>(s_arena.get(), shared);

    // bind the bytecode to call the instance now
    for (const auto& instruction : s_bytecode) s_arena->bytecode.write(instruction.encode());

    // update the buffer before continuing now
    info->buffer() = s_arena->bytecode.view();

    // ensure the function is emplace as the "main" module now
    return s_info = s_arena->functions.emplace_back(std::move(info)).get();
}

TALOS_MM_BUILTIN_FIELD(Function::Dynamic, bind, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);  // ensure size
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return isolate->bind(args.self<Function::Dynamic>(), args[0]);
}

TALOS_MM_BUILTIN_FIELD(Function::Dynamic, arity, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return Number::Tagged(args.self<Function::Dynamic>().arity());
}

TALOS_MM_BUILTIN_FIELD(Function::Dynamic, adicity, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return Number::Tagged(args.self<Function::Dynamic>().adicity());
}

TALOS_MM_BUILTIN_FIELD(Function::Dynamic, receiver, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args.self());
    return args.self<Function::Dynamic>().receiver();  // get now
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Function::Dynamic)::m_attributes(
    const Function::Dynamic&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
