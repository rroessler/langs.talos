/// Forge Modules
#include "forge/module/interface.hpp"
#include "forge/async/future.hpp"
#include "forge/bytecode/compiler.hpp"
#include "forge/document/service.hpp"
#include "forge/resource/frame.hpp"
#include "forge/runtime/isolate.hpp"
#include "forge/toolchain/audit.hpp"
#include "forge/toolchain/parse.hpp"
#include "forge/type/builder.hpp"

/// Metadata Modules
#include "forge/bytecode/metadata.hpp"
#include "forge/engine/metadata.hpp"
#include "forge/syntax/metadata.hpp"
#include "forge/type/metadata.hpp"

//  PUBLIC METHODS  //

void Forge::Module::Interface::parse(XI::Container* services) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // lock the module before parsing here
    if (m_phase < Phase::PARSED) m_parse(services, metadata<Phase::PARSED>()), m_phase = Phase::PARSED;
}

void Forge::Module::Interface::analyze(XI::Container* services) {
    // lock the incoming details now from handling
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);

    // handle when we are not at a valid phase potentially
    switch (m_phase) {
        case Phase::CLEANED: m_parse(services, metadata<Phase::PARSED>()); $_FALLTHROUGH;
        case Phase::PARSED: m_analyze(services, metadata<Phase::TYPED>()), m_phase = Phase::TYPED; break;
        default: break;  // did not encounted a valid phase to analyze here
    }
}

Forge::Linker::Arena* Forge::Module::Interface::compile(XI::Container* services) {
    // prepare the incoming details now
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    auto* codegen = metadata<Phase::COMPILED>();

    // only allow compile if correct phase
    if (!m_phase.compare_exchange_strong(Phase::TYPED, Phase::COMPILED)) return codegen->arena().get();
    return m_compile(services, codegen), codegen->arena().get();  // compile now as necessary
}

Forge::Async::Thenable* Forge::Module::Interface::interpret(Runtime::Isolate* isolate, const Resource::Trace& trace) {
    auto lock = $::Lock::scope(m_mutex);  // want to only interpret once, but access many
    auto success = m_phase.compare_exchange_strong(Phase::COMPILED, Phase::EXPORTED);
    auto* exports = metadata<Phase::EXPORTED>();        // prepare the exports to be used
    $_UNUSED $_AUTO = Resource::Frame(isolate, trace);  // trace the execution of the engine
    return lock.unlock(), success ? m_interpret(isolate, exports) : exports->deferred();
}

//  PRIVATE METHODS  //

Forge::Syntax::Dependencies Forge::Module::Interface::m_dependencies() const noexcept {
    return metadata<Phase::PARSED>()->tree()->dependencies();
}

$::Ptr::Shared<Forge::Document::Buffer> Forge::Module::Interface::m_document(XI::Container* services) const noexcept {
    if (m_resource.scheme() != $::URI::Scheme::FILE) return $::New().shared<Document::Buffer>();
    return services->get<Document::Service>()->resolve(m_resource);  // attempt resolving now
}

void Forge::Module::Interface::m_parse(XI::Container* services, Metadata::Attributes<Phase::PARSED>* syntax) {
    auto* reporter = m_reporter.get();     // prepare the lexical options
    auto document = m_document(services);  // prepare a document buffer

    // get the outgoing diagnostics encoding to be used
    auto encoding = services->get<Runtime::Options>()->diagnostics.encoding;

    // prepare the baseline options for the lexer
    Lexer::Options options = { .encoding = encoding, .reporter = reporter };

    // bind the necessary tokens and tree for the syntax
    syntax->tokens() = Toolchain::lex(*document.get(), options);
    syntax->tree() = Toolchain::parse(&syntax->tokens(), reporter);
}

void Forge::Module::Interface::m_analyze(XI::Container* services, Metadata::Attributes<Phase::TYPED>* types) {
    auto typeless = services->get<Runtime::Options>()->flags.typeless;
    Type::Options options = { .services = services, .reporter = m_reporter.get() };
    if (typeless) types->context() = $::New().unique<Type::Context>(Type::Builder::object());
    else types->context() = Toolchain::audit(metadata<Phase::PARSED>()->tree().get(), options);
}

void Forge::Module::Interface::m_compile(XI::Container* services, Metadata::Attributes<Phase::COMPILED>* codegen) {
    // pull out the underlying details to be used
    auto* syntax = metadata<Phase::PARSED>()->tree().get();
    auto* captures = &metadata<Phase::TYPED>()->context()->captures();

    // and attempt compilation now
    codegen->arena() = services->get<Bytecode::Compiler>()->process(syntax, captures);
}

Forge::Async::Thenable* Forge::Module::Interface::m_interpret(
    Runtime::Isolate* isolate, Metadata::Attributes<Phase::EXPORTED>* exports) {
    // get the underlying metadata to work with
    auto* thenable = exports->deferred();

    // get the compilation output to resolve a main function
    const auto* codegen = metadata<Phase::COMPILED>();
    auto* info = codegen->arena()->functions[0].get();

    // prepare a local scoping to now be used
    auto local_scope = (exports->open(isolate), isolate->scope());

    // construct the main module future to be resolved
    auto local_main = local_scope(isolate->create<Function::Closure>(info));
    auto local_future = local_scope(isolate->create<Async::Future>(*local_main));

    auto local_thenable = local_future->thenable();  // and await the result
    auto okay = local_scope(local_thenable->await(isolate))->traits().okay();

    // check the result is valid and handle accordingly now
    if (okay) okay = thenable->resolve(isolate, exports->close());
    else okay = thenable->reject(isolate, isolate->exception());

    // and return the thenable based on the final details
    return okay ? thenable : nullptr;
}
