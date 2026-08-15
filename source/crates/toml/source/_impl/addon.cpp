/// Crate Includes
#include "crates/toml/source/addon.hpp"

//  PROPERTIES  //

/// @brief The underlying TOML addon installer.
TALOS_MM_DYLIB_ADDON(TOML, CRATE_XX_TOML_METHODS)

//  ADDON METHODS  //

TALOS_MM_DYLIB_METHOD(TOML, encode, isolate, ) { return isolate->todo(); }
TALOS_MM_DYLIB_METHOD(TOML, decode, isolate, ) { return isolate->todo(); }
