/// Talos Modules
#include <talos/member/factory.hpp>

/// Crate Modules
#include "crates/uuid/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying UUID addon installer.
TALOS_MM_DYLIB_ADDON(UUID, CRATE_XX_UUID_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(UUID, V1, isolate, ) { return m_generate(isolate, XH::UUID::V1); }
TALOS_MM_DYLIB_METHOD(UUID, V4, isolate, ) { return m_generate(isolate, XH::UUID::V4); }
TALOS_MM_DYLIB_METHOD(UUID, V6, isolate, ) { return m_generate(isolate, XH::UUID::V6); }
TALOS_MM_DYLIB_METHOD(UUID, V7, isolate, ) { return m_generate(isolate, XH::UUID::V7); }

TALOS_MM_DYLIB_METHOD(UUID, V3, isolate, args) { return m_namespace(isolate, args, XH::UUID::V3); }
TALOS_MM_DYLIB_METHOD(UUID, V5, isolate, args) { return m_namespace(isolate, args, XH::UUID::V5); }
