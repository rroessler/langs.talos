/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_DECL(Deprecated, reader) {
    // prepare the storage instance now
    auto* storage = reader->storage();

    // attempt returning a valid token when necessary
    if (!reader->match(Lexer::Kind::LTRL_STR)) return storage->empty();

    // can safely return the deprecation string now
    auto* message = storage->unicode(reader->previous()->lexeme(), true);
    return storage->append(storage->space().hard(), message);
}
