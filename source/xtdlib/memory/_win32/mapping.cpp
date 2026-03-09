/// Library Modules
#include "xtdlib/memory/mapping.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_WINDOWS

/// Library Modules
#include "xtdlib/portable/windows.hpp"

/// Forward Declarations
$_FWD($::Memory::Windows, size_t realign(size_t))
$_FWD($::Memory::Windows, SYSTEM_INFO information())
$_FWD($::Memory::Windows, bool access(int32_t, DWORD&))
$_FWD($::Memory::Windows, bool protection(int32_t, DWORD&))
$_FWD($::Memory::Windows, $_NORETURN void* failure(const String::View&, void*, size_t))

//  MACROS  //

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_EXEC 2
#define PROT_WRITE 4

#define MAP_FIXED 32
#define MAP_PRIVATE 4
#define MAP_SHARED 2
#define MAP_ANONYMOUS 1
#define MAP_DEFAULT MAP_ANONYMOUS | MAP_PRIVATE

//  PROPERTIES  //

int32_t $::Memory::Prot::NONE = PROT_NONE;
int32_t $::Memory::Prot::READ = PROT_READ;
int32_t $::Memory::Prot::EXEC = PROT_EXEC;
int32_t $::Memory::Prot::WRITE = PROT_WRITE;

int32_t $::Memory::Flag::FIXED = MAP_FIXED;
int32_t $::Memory::Flag::PRIVATE = MAP_PRIVATE;
int32_t $::Memory::Flag::SHARED = MAP_SHARED;
int32_t $::Memory::Flag::ANONYMOUS = MAP_ANONYMOUS;
int32_t $::Memory::Flag::DEFAULT = MAP_DEFAULT;

//  PUBLIC METHODS  //

SYSTEM_INFO $::Memory::Windows::information() {
    static SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    return info;
}

size_t $::Memory::Windows::realign(size_t size) {
    static size_t granularity = information().dwAllocationGranularity;
    return Page::validate((size + granularity - 1) / granularity * granularity);
}

bool $::Memory::Windows::access(int32_t input, DWORD& access) {
    switch (input) {
        case PROT_NONE: access = 0; break;
        case PROT_READ: access = FILE_MAP_READ; break;
        case PROT_EXEC: access = FILE_MAP_EXECUTE; break;
        case PROT_READ | PROT_EXEC: access = FILE_MAP_READ | FILE_MAP_EXECUTE; break;
        case PROT_READ | PROT_WRITE: access = FILE_MAP_READ | FILE_MAP_WRITE; break;
        case PROT_READ | PROT_WRITE | PROT_EXEC: access = FILE_MAP_READ | FILE_MAP_WRITE | FILE_MAP_EXECUTE; break;
        default: return false;  // should fail for bad matches
    }

    // should be valid now
    return true;
}

bool $::Memory::Windows::protection(int32_t input, DWORD& output) {
    switch (input) {
        case PROT_NONE: output = PAGE_NOACCESS; break;
        case PROT_READ: output = PAGE_READONLY; break;
        case PROT_EXEC: output = PAGE_EXECUTE; break;
        case PROT_READ | PROT_EXEC: output = PAGE_EXECUTE_READ; break;
        case PROT_READ | PROT_WRITE: output = PAGE_READWRITE; break;
        case PROT_READ | PROT_WRITE | PROT_EXEC: output = PAGE_EXECUTE_READWRITE; break;
        default: return false;  // should fail for bad matches
    }

    // should be valid now
    return true;
}

$_NORETURN void* $::Memory::Windows::failure(const String::View& label, void* address, size_t size) {
    // prepare the buffer to hold the error message
    LPSTR buffer = nullptr;

    // Ask Win32 to give us the string version of that message ID.
    // The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet
    // know how long the message string will be).
    size_t mlen =
        ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, ::GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, nullptr);

    // Copy the error message into a string
    auto message = $::String::Buffer(buffer, mlen);
    ::LocalFree(buffer);  // free the buffer now

    // and show the final failure now
    $_ABORT("Could not ::{0} {1} bytes at address {2}. Reason: {3}", label, size, address, message);
}

size_t $::Memory::Page::size() {
    static size_t ps = Windows::information().dwPageSize;
    return ps;  // ensure only ever cached once
}

void $::Memory::Map::free(void* address, size_t size) {
    if (::UnmapViewOfFile(address)) return;
    if (::VirtualFree(address, 0, MEM_RELEASE)) return;
    Windows::failure("VirtualFree", address, size);
}

bool $::Memory::Map::protect(void* address, size_t size, int32_t prot) {
    DWORD _, flProt, flAccess;  // attempt parsing out
    if (!Windows::access(prot, flAccess)) return false;
    if (!Windows::protection(prot, flProt)) return false;
    return ::VirtualProtect(address, size, flProt, &_);
}

void* $::Memory::Map::alloc(void* address, size_t size, int32_t prot, int32_t flags) {
    DWORD flProt, flAccess;  // attempt parsing out into our necessary items
    if (!Windows::access(prot, flAccess)) return Windows::failure("Access", address, size);
    if (!Windows::protection(prot, flProt)) return Windows::failure("Protection", address, size);

    // handle our output as necessary now
    if (!(flags & MAP_ANONYMOUS) && (flags & MAP_SHARED)) {
        const DWORD dwMaximumSizeLow = (DWORD)(size & 0xFFFFFFFF);
        const DWORD dwMaximumSizeHigh = (DWORD)((size >> 32) & 0xFFFFFFFF);

        HANDLE h = flags & MAP_ANONYMOUS ? INVALID_HANDLE_VALUE : (HANDLE)_get_osfhandle(-1);
        HANDLE fmh = ::CreateFileMapping(h, nullptr, flProt, dwMaximumSizeHigh, dwMaximumSizeLow, nullptr);
        if (fmh == nullptr) return Windows::failure("CreateFileMapping", address, size);  // failed to create

        // ensure we have a valid set of details now
        void* _ = ::MapViewOfFileEx(fmh, flAccess, (DWORD)(0), (DWORD)(0), 0, address);
        return ::CloseHandle(fmh), _ == nullptr ? (Windows::failure("MapViewOfFileEx", address, size), nullptr) : _;
    }

    // we have a virtual allocation to be performed instead of file-mapping
    void* retval = ::VirtualAlloc(address, Windows::realign(size), MEM_COMMIT | MEM_RESERVE, flProt);
    return retval == nullptr ? (Windows::failure("VirtualAlloc", address, size), nullptr) : retval;
}

void* $::Memory::Map::alloc(size_t size, int32_t prot, int32_t flags) { return alloc(nullptr, size, prot, flags); }

#endif
