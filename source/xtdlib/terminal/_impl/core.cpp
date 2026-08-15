/// Library Includes
#include "xtdlib/terminal/core.hpp"
#include "xtdlib/system/platform.hpp"

//  MACROS  //

#if $_PLATFORM_WINDOWS
#define MM_FILENO(S) ::_fileno(S)
#define MM_ATTY(H) ::_isatty(H)
#else
#define MM_FILENO(S) fileno(S)
#define MM_ATTY(H) ::isatty(H)
#endif

//  PUBLIC METHODS  //

bool $::Terminal::is(int32_t fh) { return MM_ATTY(fh); }
bool $::Terminal::is(FILE *file) { return file && is(MM_FILENO(file)); }
bool $::Terminal::is(const std::ostream &stream) { return is(as(stream)); }
FILE *$::Terminal::as(const std::ostream &stream) {
  if (&stream == &std::cout) return stdout;
  else if (&stream == &std::cerr) return stderr;
  return &stream == &std::clog ? stderr : nullptr;
}
