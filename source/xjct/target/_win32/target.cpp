/// Platform Modules
#include "xjct/target/windows.hpp"

#if $_PLATFORM_WINDOWS

/// Windows Modules
#include <xtdlib/portable/windows.hpp>

//  PRIVATE METHODS  //

XJCT::Archive::Blob XJCT::Target::Windows::m_resource(const $::String::View& name) const noexcept {
    auto resource = $::Convert::uppercase(name);  // ensure we uppercase the name
    auto handle = ::FindResourceA(NULL, resource.c_str(), MAKEINTRESOURCEA(10));
    if (handle == INVALID_HANDLE_VALUE) return "";  // failed to find the resource

    // prepare the baseline details now
    auto global = ::LoadResource(NULL, handle);
    auto size = global ? ::SizeofResource(NULL, handle) : 0;

    // attempt getting the pointer now
    auto* ptr = ::LockResource(global);
    if (ptr == NULL) return "";

    // resolve the final resource now
    return { reinterpret_cast<const char*>(ptr), size };
}

#endif
