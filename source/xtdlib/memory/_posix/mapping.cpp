/// Library Modules
#include "xtdlib/memory/mapping.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/system/platform.hpp"

#if $_PLATFORM_POSIX

/// Unix Modules
#include <sys/mman.h>
#include <unistd.h>

/// Forward Declarations
$_FWD($_NORETURN void failure(const String::View&, void*, size_t), $::Memory::Unix)

//  PROPERTIES  //

int32_t $::Memory::Prot::NONE = PROT_NONE;
int32_t $::Memory::Prot::READ = PROT_READ;
int32_t $::Memory::Prot::EXEC = PROT_EXEC;
int32_t $::Memory::Prot::WRITE = PROT_WRITE;

int32_t $::Memory::Flag::FIXED = MAP_FIXED;
int32_t $::Memory::Flag::PRIVATE = MAP_PRIVATE;
int32_t $::Memory::Flag::SHARED = MAP_SHARED;
int32_t $::Memory::Flag::ANONYMOUS = MAP_ANONYMOUS;
int32_t $::Memory::Flag::DEFAULT = MAP_ANONYMOUS | MAP_PRIVATE;

//  PUBLIC METHODS  //

$_NORETURN void $::Memory::Unix::failure(const String::View& label, void* address, size_t size) {
    $_ABORT("Could not ::{0} {1} bytes at address {2}", label, size, address);
}

size_t $::Memory::Page::size() {
    static size_t ps = ::sysconf(_SC_PAGE_SIZE);
    return ps;  // ensure only ever cached once
}

void $::Memory::Map::free(void* address, size_t size) {
    if (::munmap(address, Page::validate(size))) Unix::failure("unmap", address, size);
}

bool $::Memory::Map::protect(void* address, size_t size, int32_t prot) { return ::mprotect(address, size, prot) == 0; }

void* $::Memory::Map::alloc(void* address, size_t size, int32_t prot, int32_t flags) {
    void* memory = ::mmap(address, Page::validate(size), prot, flags, -1, 0);
    return memory ? memory : (Unix::failure("map", address, size), nullptr);
}

void* $::Memory::Map::alloc(size_t size, int32_t prot, int32_t flags) {
    // map the initial aligned memory
    auto memory = alloc(nullptr, size * 2, prot, flags);
    auto pointer = reinterpret_cast<uintptr_t>(memory);

    // get the excess details (and ensure aligned)
    size_t excess_upper = Page::aligned(pointer % size);
    size_t excess_lower = Page::aligned(size - excess_upper);

    // stop if allocation is already optimally aligned
    if (excess_lower == size) return free(memory, size), reinterpret_cast<void*>(pointer + size);

    uintptr_t lower_excess_base = pointer;  // unmap any excess pages
    uintptr_t upper_excess_base = pointer + (size * 2) - excess_upper;
    free(reinterpret_cast<void*>(lower_excess_base), excess_lower);
    free(reinterpret_cast<void*>(upper_excess_base), excess_upper);

    // and return the resulting self-aligned memory
    uintptr_t aligned_base = pointer + excess_lower;
    $_ASSERT(aligned_base % size == 0, "Alignment mismatch");
    return reinterpret_cast<void*>(aligned_base);
}

#endif
