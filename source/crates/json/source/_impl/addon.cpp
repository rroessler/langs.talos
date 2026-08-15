/// Crate Includes
#include "crates/json/source/addon.hpp"

//  PROPERTIES  //

/// @brief The underlying JSON addon installer.
TALOS_MM_DYLIB_ADDON(JSON, CRATE_XX_JSON_METHODS)

//  ADDON METHODS  //

TALOS_MM_DYLIB_METHOD(JSON, encode, isolate, ) { return isolate->todo(); }
TALOS_MM_DYLIB_METHOD(JSON, decode, isolate, ) { return isolate->todo(); }
