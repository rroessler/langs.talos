/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PUBLIC METHODS  //

TALOS_MM_FORMAT_INFIX(Typed, reader, value) { return m_specialize(reader, value); }
