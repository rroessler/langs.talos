/// Forge Modules
#include "forge/toolchain/format.hpp"
#include "forge/diagnostic/reporter.hpp"
#include "forge/format/pipeline.hpp"
#include "forge/lexer/dispatch.hpp"
#include "forge/toolchain/parse.hpp"

//  PUBLIC METHODS  //

Forge::Format::Result Forge::Toolchain::format(const $::String::View& buffer, const Format::Options& options) {
    return format(Document::Buffer(buffer), options);
}

Forge::Format::Result Forge::Toolchain::format(const Document::Buffer& document, const Format::Options& options) {
    // prepare an empty reporter to be used
    auto reporter = Diagnostic::Reporter();

    // parse our tokens and our syntax-tree to be used for formatting
    auto tokens = lex(document, { .comments = true, .reporter = &reporter });

    // fail early where possible to do so
    if (reporter.failed()) return std::nullopt;

    // construct a formatting pipeline to render our document
    return Format::Pipeline().process(&tokens, &options);
}
