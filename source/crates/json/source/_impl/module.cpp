/// Talos Modules
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/json/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying JSON addon installer.
TALOS_MM_DYLIB_ADDON(JSON, CRATE_XX_JSON_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(JSON, encode, isolate, ) { return isolate->todo(); }
TALOS_MM_DYLIB_METHOD(JSON, decode, isolate, ) { return isolate->todo(); }
