/// Forge Modules
#include "forge/format/dispatch.hpp"

//  PRIVATE METHODS  //

Forge::Format::Node* Forge::Format::Dispatch::m_statement(Reader* reader, Node::Group* group) {
    switch (reader->current()->kind()) {
        // blocks get some special treatment here
        case Lexer::Kind::PUNC_LBRACE: return m_block(reader, group);

        // handle each of our incoming statement types
        case Lexer::Kind::LOOP_FOR: return m_statement<Syntax::For>(reader);
        case Lexer::Kind::LOOP_ANY: return m_statement<Syntax::Loop>(reader);
        case Lexer::Kind::FLOW_IF: return m_statement<Syntax::Conditional>(reader);

        case Lexer::Kind::FLOW_BREAK: return m_terminates<Syntax::Break>(reader);
        case Lexer::Kind::FLOW_CONT: return m_terminates<Syntax::Continue>(reader);
        case Lexer::Kind::FLOW_RETURN: return m_terminates<Syntax::Return>(reader);

        // otherwise attempt matching a suitable expression instead
        default: return m_terminates(reader, m_expression(reader));
    }
}
