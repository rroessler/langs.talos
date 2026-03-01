/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_FORMAT_PREFIX(True, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
FORGE_MM_FORMAT_PREFIX(False, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
