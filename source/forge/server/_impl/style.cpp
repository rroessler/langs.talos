/// Forge Modules
#include "forge/server/style.hpp"

/// Type Modules
#include "forge/type/_inline/type.ipp"

//  PROPERTIES  //

/// @brief The baseline typing style.
static constexpr auto g_typing_failed = "";

//  PUBLIC METHODS  //

$::String::Buffer Forge::Server::Style::typing(const Relint::Mirror *mirror) {
    // prepare the baseline details if we having invalid details
    if ($_UNLIKELY(mirror == nullptr)) return g_typing_failed;

    // prepare the visitors to be used now
    Relint::Overloads visitors = {
        // for regular mirrors we will return the base typing
        [](const Relint::Mirror *mirror) { return mirror->typing(); },

        // for certain syntax nodes, we want no output to be shown
        [](const Syntax::Import *) -> Type::Erased { return nullptr; },

        // for call operations we should lookup the function typing instead
        [](const Syntax::Call *call) { return call->callee()->traits()->type(); },

        // for spawn operations, we want to transform the return-type to be asynchronous
        [](const Syntax::Spawn *spawn) { return Type::Builder::asyncify(spawn->callee()->traits()->type()); },
    };

    // attempt visiting our nodes as necessary now
    auto type = mirror->visit(std::move(visitors));

    // ensure our typing is valid before continuing
    if (type == nullptr || type->is<Type::Unset, Type::Failure>()) return g_typing_failed;

    // otherwise we want to format to a string value now
    return fmt::to_string(*type);
}
