/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_FORMAT_PREFIX(Text, reader) { return reader->storage()->unicode(reader->advance()->lexeme(), true); }
