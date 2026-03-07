/// Talos Modules
#include "talos/syntax/generator.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

Talos::Syntax::Expression* Talos::Parser::Dispatch::m_expression(Stream* parser, Precedence rank) {
    return Syntax::Generator::expression<Syntax::Expression, Stream, Dispatch>(parser, rank);
}
