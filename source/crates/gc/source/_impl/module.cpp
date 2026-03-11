/// Talos Modules
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/gc/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying garbage addon installer.
TALOS_MM_DYLIB_ADDON(Garbage, CRATE_XX_GARBAGE_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(Garbage, cycles, isolate, ) { return Number::Tagged(isolate->service<Service>()->cycles()); }

TALOS_MM_DYLIB_METHOD(Garbage, collect, isolate, args) {
    auto value = args.at(0, Value::Boolean(0));  // prepare
    TALOS_MM_ASSERT_TYPEOF(isolate, Value::Boolean, value);
    auto major = value.as<Value::Boolean>().state();

    auto *garbage = isolate->service<Service>();  // prepare the collector
    isolate->thread()->native([major, garbage] { garbage->collect(major); });

    // ensure we resolve as done now
    return Value::Void();
}
