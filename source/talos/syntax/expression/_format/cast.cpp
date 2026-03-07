/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_FORMAT_INFIX(Cast, reader, value) {
    return m_binary(reader, value, [](Reader* reader) { return m_annotation(reader); });
}
