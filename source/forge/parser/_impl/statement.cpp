/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Node* Forge::Parser::Dispatch::m_statement(Stream* parser) {
    switch (parser->current()->kind()) {
        // ignore additional terminators when found
        case Lexer::Kind::PUNC_TERM: return parser->advance(), nullptr;

        // handle all the potential statements that we have
        case Lexer::Kind::LOOP_FOR: return m_statement<Syntax::For>(parser);
        case Lexer::Kind::LOOP_ANY: return m_statement<Syntax::Loop>(parser);
        case Lexer::Kind::PUNC_LBRACE: return m_statement<Syntax::Block>(parser);
        case Lexer::Kind::FLOW_IF: return m_statement<Syntax::Conditional>(parser);

        case Lexer::Kind::FLOW_BREAK: return m_terminates<Syntax::Break>(parser, "a break statement");
        case Lexer::Kind::FLOW_CONT: return m_terminates<Syntax::Continue>(parser, "a continue statement");
        case Lexer::Kind::FLOW_RETURN: return m_terminates<Syntax::Return>(parser, "a return statement");

        // otherwise attempt matching a suitable expression
        default: return m_terminates(parser, m_expression(parser), "an expression");
    }
}
