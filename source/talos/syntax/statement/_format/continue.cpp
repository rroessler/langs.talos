/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_STMT(Continue, reader, ) { return reader->storage()->unicode(reader->advance()->lexeme()); }
