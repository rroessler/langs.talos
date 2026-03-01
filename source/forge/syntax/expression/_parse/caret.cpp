/// Forge Modules
#include "forge/parser/delimited.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_PREFIX(Caret, parser, ) { return parser->allocate<Syntax::Caret>(parser->advance()); }
