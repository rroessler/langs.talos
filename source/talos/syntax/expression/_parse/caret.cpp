/// Talos Modules
#include "talos/parser/delimited.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Caret, parser, ) { return parser->allocate<Syntax::Caret>(parser->advance()); }
