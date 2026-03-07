/// Talos Modules
#include "talos/toolchain/format.hpp"
#include "talos/diagnostic/reporter.hpp"
#include "talos/format/pipeline.hpp"
#include "talos/lexer/dispatch.hpp"
#include "talos/toolchain/parse.hpp"

//  PUBLIC METHODS  //

Talos::Format::Result Talos::Toolchain::format(const $::String::View& buffer, const Format::Options& options) {
    return format(Document::Buffer(buffer), options);
}

Talos::Format::Result Talos::Toolchain::format(const Document::Buffer& document, const Format::Options& options) {
    // prepare an empty reporter to be used
    auto reporter = Diagnostic::Reporter();

    // parse our tokens and our syntax-tree to be used for formatting
    auto tokens = lex(document, { .comments = true, .reporter = &reporter });

    // fail early where possible to do so
    if (reporter.failed()) return std::nullopt;

    // construct a formatting pipeline to render our document
    return Format::Pipeline().process(&tokens, &options);
}
