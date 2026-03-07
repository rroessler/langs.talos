/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_PREFIX(True, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
TALOS_MM_FORMAT_PREFIX(False, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
