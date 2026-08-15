/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_PREFIX(True, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
TALOS_MM_FORMAT_PREFIX(False, reader) { return reader->storage()->unicode(reader->advance()->lexeme()); }
