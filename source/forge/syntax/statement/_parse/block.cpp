/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Block* Forge::Parser::Dispatch::m_block(Stream* parser, bool module) {
    // prepare the snapshot to be used now
    auto snapshot = parser->snapshot();

    // ensure there is an opening for a block statement now
    if (!parser->expect(Lexer::Kind::PUNC_LBRACE)) return nullptr;

    // prepare the output of the block to be used now
    auto statements = std::vector<Syntax::Node*>();

    // attempt parsing declarations whilst possible to do so
    while (!parser->check(Lexer::Kind::PUNC_RBRACE) && !parser->eos()) {
        auto* node = m_declaration(parser, module);
        if (node == nullptr) return nullptr;
        statements.emplace_back(node);
    }

    // ensure we have a final brace now
    if (!parser->expect(Lexer::Kind::PUNC_RBRACE)) return nullptr;

    // and construct the resulting block
    return parser->allocate<Syntax::Block>(statements, snapshot);
}

FORGE_MM_PARSE_STMT(Block, parser) { return m_block(parser, false); }
