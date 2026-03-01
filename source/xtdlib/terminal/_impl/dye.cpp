/// Library Modules
#include "xtdlib/terminal/dye.hpp"
#include "xtdlib/terminal/core.hpp"

//  PROPERTIES  //

static bool g_enabled = true;
static int32_t g_index = std::ios_base::xalloc();

//  PUBLIC METHODS  //

bool $::Dye::enabled() { return g_enabled; }
void $::Dye::enabled(bool state) { g_enabled = state; }

bool $::Dye::enabled(Stream::Handle* stream) { return enabled() && Terminal::is(stream); }
bool $::Dye::enabled(Stream::Output& stream) { return enabled() && (Terminal::is(stream) || stream.iword(g_index)); }
$::Stream::Output& $::Dye::enabled(Stream::Output& stream, bool state) { return stream.iword(g_index) = state, stream; }
