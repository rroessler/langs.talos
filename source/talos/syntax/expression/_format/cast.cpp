/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PUBLIC METHODS  //

TALOS_MM_FORMAT_INFIX(Cast, reader, value) {
  return m_binary(reader, value, [](Reader *reader) { return m_annotation(reader); });
}
