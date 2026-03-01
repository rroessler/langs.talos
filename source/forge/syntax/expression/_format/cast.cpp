/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

FORGE_MM_FORMAT_INFIX(Cast, reader, value) {
    return m_binary(reader, value, [](Reader* reader) { return m_annotation(reader); });
}
