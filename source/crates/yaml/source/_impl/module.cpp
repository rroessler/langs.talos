/// Talos Modules
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/yaml/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying YAML addon installer.
TALOS_MM_DYLIB_ADDON(YAML, CRATE_XX_YAML_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(YAML, encode, isolate, ) { return isolate->todo(); }
TALOS_MM_DYLIB_METHOD(YAML, decode, isolate, ) { return isolate->todo(); }
