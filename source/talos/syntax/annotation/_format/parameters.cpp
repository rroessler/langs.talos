/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_parameters(Reader* reader) {
    return m_annotation<Syntax::Parameters>(reader);
}

TALOS_MM_FORMAT_HINT(Parameters, reader) {
    // prepare the incoming storage to be used
    auto* storage = reader->storage();

    // check if there are no parameters available at all
    if (!reader->match(Lexer::Kind::PUNC_LPAREN)) return storage->empty();

    // prepare the callback and exit condition to be used
    auto callback = [storage](Reader* reader) -> Node* {
        auto spread = reader->match(Lexer::Kind::PUNC_SPREAD);
        auto* parameter = m_variable(reader, true);  // compressed params
        if (parameter == nullptr) return nullptr;    // failed to parse
        return spread ? storage->append(storage->spread(), parameter) : parameter;
    };

    // attempt parsing out the collection required now
    auto* parameters = m_delimited(reader, { std::move(callback), Lexer::Kind::PUNC_RPAREN });
    if (parameters == nullptr || !reader->match(Lexer::Kind::PUNC_RPAREN)) return nullptr;

    // prepare the necessary indentation now
    parameters = storage->indent(storage->line().soft(), parameters);

    // prepare the leading and trailing details to be used
    auto* trailing = storage->list(storage->line().soft(), storage->paren().right());

    // and construct the resulting group to be returned now
    return storage->group(storage->paren().left(), parameters, trailing);
}
