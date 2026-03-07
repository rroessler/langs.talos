/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_PREFIX(Void, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
