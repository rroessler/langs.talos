/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PRIVATE METHODS  //

Talos::Format::Piece *Talos::Format::Dispatch::m_parameters(Reader *reader, bool) {
  // prepare the incoming storage to be used
  auto *storage = reader->storage();

  // check if there are no parameters available at all
  if (!reader->match(Lexer::Kind::PUNC_LPAREN)) return storage->empty();

  // prepare the callback and exit condition to be used
  auto callback = [storage](Reader *reader) -> Piece * {
    auto spread = reader->match(Lexer::Kind::PUNC_SPREAD);
    auto *parameter = m_variable(reader, true); // compressed params
    if (parameter == nullptr) return nullptr;   // failed to parse
    return spread ? storage->append(storage->spread(), parameter) : parameter;
  };

  // attempt parsing out the collection required now
  auto *parameters = m_delimited(reader, {std::move(callback), Lexer::Kind::PUNC_RPAREN});
  if (parameters == nullptr || !reader->match(Lexer::Kind::PUNC_RPAREN)) return nullptr;

  // prepare the necessary indentation now
  parameters = storage->indent(storage->line().soft, parameters);

  // prepare the leading and trailing details to be used
  auto *trailing = storage->list(storage->line().soft, storage->paren().right);

  // and construct the resulting group to be returned now
  return storage->group(storage->paren().left, parameters, trailing);
}

TALOS_MM_FORMAT_HINT(Parameters, reader) { return m_parameters(reader, true); }
TALOS_MM_FORMAT_DECL(Parameters, reader) { return m_parameters(reader, false); }
