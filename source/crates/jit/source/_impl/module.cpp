/// Talos Modules
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>
#include "talos/machine/service.hpp"

/// Crate Modules
#include "crates/jit/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying JIT addon installer.
TALOS_MM_DYLIB_ADDON(JIT, CRATE_XX_JIT_METHODS)

//  CONSTRUCTORS  //

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(JIT, compile, isolate, args) {
    // ensure the correct incoming details now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // if we do not have a closure-based value, then passthrough
    if (!args[0].is<Function::Closure>()) return args[0];

    // get the incoming machine service now
    auto *machine = isolate->service<Machine::Service>();

    // and attempt compilation as necessary now
    return machine->compile(isolate, args.at<Function::Closure>(0));
}
