/// Forge Modules
#include <forge/member/factory.hpp>

/// Assert Modules
#include <forge/builtins/_inline/assert.ipp>
#include "forge/machine/service.hpp"

/// Crate Modules
#include "crates/jit/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying JIT addon installer.
FORGE_MM_DYLIB_ADDON(JIT, CRATE_XX_JIT_METHODS)

//  CONSTRUCTORS  //

//  PRIVATE METHODS  //

FORGE_MM_DYLIB_METHOD(JIT, compile, isolate, args) {
    // ensure the correct incoming details now
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // if we do not have a closure-based value, then passthrough
    if (!args[0].is<Function::Closure>()) return args[0];

    // get the incoming machine service now
    auto *machine = isolate->service<Machine::Service>();

    // and attempt compilation as necessary now
    return machine->compile(isolate, args.at<Function::Closure>(0));
}
