/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

Forge::Format::Node* Forge::Format::Dispatch::m_block(Reader* reader, Node::Group* group) {
    // attempt eating the incoming open-brace
    if (!reader->match(Lexer::Kind::PUNC_LBRACE)) return nullptr;

    // get the underlying storage instance
    auto* options = reader->options();
    auto* storage = reader->storage();

    // attempt eating the incoming collection now
    auto* statements = m_collection(reader, { Lexer::Kind::PUNC_RBRACE });

    // ensure we have a closing brace now as well
    if (statements == nullptr || !reader->match(Lexer::Kind::PUNC_RBRACE)) return nullptr;

    // construct the items that we could use for construction
    auto* block = storage->group();
    auto* header = group ? group : block;

    // determine the brace styling to be used
    auto* style = options->braces_preserve ? storage->space().hard() : storage->line().hard();
    storage->append(header, group ? style : storage->empty(), storage->brace().left());

    // stop early when possible to do so
    if (statements->empty()) return storage->append(header, storage->brace().right()), block;

    // force expansion of nodes when necessary to do so
    if (!options->braces_compress) storage->append(statements, storage->expand());

    // ensure that the statements have the necessary indentation as well
    statements = storage->indent(storage->line().dynamic(), statements);

    // construct the resulting grouping to be used now
    return storage->append(block, statements, storage->line().dynamic(), storage->brace().right());
}

FORGE_MM_FORMAT_STMT(Block, reader) { return m_block(reader); }
