/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

TALOS_MM_FORMAT_PREFIX(Panic, reader) { return m_statement<Syntax::Return>(reader); }
