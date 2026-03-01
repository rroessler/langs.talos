/// Library Modules
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/system/platform.hpp"

//  MACROS  //

#if $_PLATFORM_WINDOWS
#define MM_FILENO(S) _fileno(S)
#else
#define MM_FILENO(S) fileno(S)
#endif

//  PUBLIC METHODS  //

bool $::Terminal::is(Stream::Handle* file) { return file && is(MM_FILENO(file)); }
bool $::Terminal::is(const Stream::Output& stream) { return is(as(stream)); }
$::Stream::Handle* $::Terminal::as(const Stream::Output& stream) {
    if (&stream == &std::cout) return stdout;
    else if (&stream == &std::cerr) return stderr;
    return &stream == &std::clog ? stderr : nullptr;
}
