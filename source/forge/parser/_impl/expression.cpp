/// Forge Modules
#include "forge/syntax/generator.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Expression* Forge::Parser::Dispatch::m_expression(Stream* parser, Precedence rank) {
    return Syntax::Generator::expression<Syntax::Expression, Stream, Dispatch>(parser, rank);
}
