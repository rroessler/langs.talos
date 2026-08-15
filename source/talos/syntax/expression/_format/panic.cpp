/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PUBLIC METHODS  //

TALOS_MM_FORMAT_PREFIX(Panic, reader) { return m_statement<Syntax::Return>(reader); }
