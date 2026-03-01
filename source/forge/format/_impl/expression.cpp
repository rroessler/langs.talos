/// Forge Modules
#include "forge/format/dispatch.hpp"
#include "forge/syntax/generator.hpp"

//  PRIVATE METHODS  //

Forge::Format::Node* Forge::Format::Dispatch::m_expression(Reader* reader, Precedence rank) {
    return Syntax::Generator::expression<Node, Reader, Dispatch>(reader, rank);
}

Forge::Format::Node* Forge::Format::Dispatch::m_assignment(Reader* reader, Node* target) {
    return m_assignment(reader, target, [](Reader* reader) { return m_expression(reader); });
}

Forge::Format::Node* Forge::Format::Dispatch::m_assignment(Reader* reader, Node* target, Callback&& callback) {
    // match any incoming assignable token
    if (target == nullptr || !reader->match(Lexer::Flag::ASSIGNABLE)) return target;

    // prepare the underlying node storage now
    auto* storage = reader->storage();

    // get a unicode copy of the assignment now
    auto token = storage->unicode(reader->previous()->lexeme());

    // attempt parsing the resulting assignment now
    auto* expression = m_leading(reader, std::move(callback));
    if (expression == nullptr) return nullptr;  // failed to parse

    // construct the necessary output now to be used
    expression = storage->indent(storage->space().hard(), expression);
    return storage->append(target, storage->space().hard(), token, expression);
}
