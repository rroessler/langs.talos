/// Library Modules
#include "xtdlib/terminal/dye.hpp"
#include "xtdlib/terminal/core.hpp"

//  PROPERTIES  //

static bool g_enabled = true;
static bool g_progress = true;
static int32_t g_index = std::ios_base::xalloc();

//  PUBLIC METHODS  //

bool $::Dye::enabled() { return g_enabled; }
void $::Dye::enabled(bool state) { g_enabled = state; }

bool $::Dye::progress() { return g_progress; }
void $::Dye::progress(bool state) { g_progress = state; }

bool $::Dye::enabled(Stream::Handle* stream) { return enabled() && Terminal::is(stream); }
bool $::Dye::enabled(Stream::Output& stream) { return enabled() && (Terminal::is(stream) || stream.iword(g_index)); }
$::Stream::Output& $::Dye::enabled(Stream::Output& stream, bool state) { return stream.iword(g_index) = state, stream; }

bool $::Dye::progress(Stream::Handle* stream) { return progress() && Terminal::is(stream); }
bool $::Dye::progress(Stream::Output& stream) { return progress() && Terminal::is(stream); }
