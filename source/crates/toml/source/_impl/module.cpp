/// Talos Modules
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/toml/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying TOML addon installer.
TALOS_MM_DYLIB_ADDON(TOML, CRATE_XX_TOML_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(TOML, encode, isolate, ) { return isolate->todo(); }
TALOS_MM_DYLIB_METHOD(TOML, decode, isolate, ) { return isolate->todo(); }
