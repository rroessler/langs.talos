/// Talos Modules
#include "talos/module/service.hpp"
#include "talos/async/service.hpp"
#include "talos/async/thenable.hpp"
#include "talos/crate/constants.hpp"
#include "talos/crate/service.hpp"
#include "talos/engine/metadata.hpp"
#include "talos/module/archived.hpp"
#include "talos/module/graph.hpp"
#include "talos/runtime/container.hpp"
#include "talos/runtime/isolate.hpp"

/// Loader Modules
#include "talos/module/dynamic.hpp"
#include "talos/module/script.hpp"

//  X-MACROS  //

#define XX_IMPORT_LOADERS(X) \
    X(Script)                \
    X(Dynamic)

//  CONSTRUCTORS  //

Talos::Import::Service::Service() : Service($::Global::get<Runtime::Container>()) {}
Talos::Import::Service::Service(XI::Container* services) : m_services(services) {
#define X(N, ...)                                         \
    auto N = $::New().unique<Loader::Proxy<Module::N>>(); \
    m_loaders.emplace(N->scheme(), std::move(N));
    XX_IMPORT_LOADERS(X)
#undef X
}

//  PUBLIC METHODS  //

Talos::Import::Statistics Talos::Import::Service::analyze(const $::URI::View& resource, bool report) {
    return analyze(resource.buffer(), report);
}

Talos::Import::Statistics Talos::Import::Service::analyze(
    const $::URI::View& resource, Diagnostic::Reporter* reporter, bool display) {
    return analyze(resource.buffer(), reporter, display);
}

Talos::Import::Statistics Talos::Import::Service::analyze(const $::URI::Buffer& resource, bool report) {
    return analyze(std::vector({ resource }), report);
}

Talos::Import::Statistics Talos::Import::Service::analyze(
    const $::URI::Buffer& resource, Diagnostic::Reporter* reporter, bool display) {
    return analyze(std::vector({ resource }), reporter, display);
}

Talos::Import::Statistics Talos::Import::Service::analyze(const Dependencies& dependencies, bool report) {
    auto reporter = report ? m_services->get<Diagnostic::Reporter>() : nullptr;
    return analyze(dependencies, reporter.get(), report);  // handle analyzing now
}

Talos::Import::Statistics Talos::Import::Service::analyze(
    const Dependencies& dependencies, Diagnostic::Reporter* collector, bool display) {
    // prepare the expected severity value
    size_t errors = 0, hints = 0, sources = 0;

    // prepare the spinner to be used
    $::Spinner::Shared spinner = nullptr;

    // check if using verbose output at all
    auto* options = m_services->get<Runtime::Options>();
    auto verbose = collector && options->flags.verbose && display;

    // prepare the suffix constructor to be used now
    static constexpr auto suffix = [](const $::String::View& message) {
        auto prefix = $::Convert::stringify($::Dye::green("Analyzing"));
        return prefix + ": " + $::Convert::stringify($::Dye::dim(message));
    };

    // prepare a spinner instance if necessary
    auto* async = m_services->get<Async::Service>();
    if (verbose) spinner = async->spinner(suffix("Loading Modules..."));

    // get an initial starting time-point
    auto start = $::Clock::Performance();

    // prepare the underlying graph-view
    auto view = graph(dependencies);
    auto leaves = view->leaves();

    // analyze our leaves in reverse breadth-first search order
    for (auto* module : std::views::reverse(leaves)) {
        // show the current module being checked here
        if (spinner) spinner->suffix(suffix("'" + module->resource().relative() + "'"));

        // analyze the module now
        module->analyze(m_services);

        auto* reporter = module->reporter();  // get the diagnostics
        auto count = reporter->errors();      // count total errors
        hints += reporter->size() - count;    // keep track of hints

        // update the current statistics to be shown
        if (count) errors += count, ++sources;
        if (collector) collector->collect(*reporter);
    }

    // show the baseline spinner as well if necessary
    if (spinner) {
        auto elapsed = $::Clock::Performance() - start;  // get time
        static constexpr auto message = "Analyzed {0} module(s) in {1}";
        spinner->dismiss(suffix(fmt::format(message, leaves.size(), elapsed)));
    }

    // report our errors if they have been found at all
    if (display && collector && collector->size()) $::IO::cerr() << (spinner ? "\n" : "") << *collector << "\n\n";

    // show the verbose details when necessary too
    if (display && collector) {
        if (hints) $::IO::eprintln("- Found {0} linting diagnostic(s)", hints);
        if (errors) $::IO::eprintln("- Found {0} error(s) across {1} file(s)", errors, sources);
    }

    // return the final errors count
    return { .errors = errors, .hints = hints };
}

Talos::Module::Interface* Talos::Import::Service::fetch(const $::URI::View& resource) {
    // pre-fail if there is already an unresolved scheme found
    $_ASSERT(resource.scheme() != $::URI::Scheme::HREF, "Cannot fetch unresolved 'href' resources");

    // check if the resource exists currently
    if (auto* module = m_drafts->lookup(resource)) return m_prepare(module);

    // attempt getting the associated loader now
    auto iter = m_loaders.find(resource.scheme());
    if (iter == m_loaders.end()) return nullptr;

    // resolve the module instance before emplacing
    auto module = iter->second->fetch(resource, m_services);
    return m_prepare(m_drafts->emplace(std::move(module)));
}

void Talos::Import::Service::preload(std::vector<$::Ptr::Unique<Linker::Arena>>&& arenas) {
    for (auto&& arena : arenas) m_drafts->emplace($::New().unique<Module::Archived>(std::move(arena)));
}

Talos::Async::Thenable* Talos::Import::Service::import(Runtime::Isolate* isolate, const $::URI::View& resource) {
    return import(isolate, resource, {});
}

Talos::Async::Thenable* Talos::Import::Service::import(
    Runtime::Isolate* isolate, const $::URI::View& resource, const Resource::Trace& trace) {
    auto* module = fetch(resource);  // attempt getting the module to be imported
    if (module == nullptr) return isolate->panic(8000102, resource.relative()), nullptr;

    // ensure we have a module that is in the correct state before continuing
    switch (module->phase()) {
        // ensure we parse and analyze the incoming module now
        case Module::Phase::CLEANED: module->parse(m_services); $_FALLTHROUGH;
        case Module::Phase::PARSED: module->analyze(m_services); $_FALLTHROUGH;

        // break when we have typed/compiled outputs
        case Module::Phase::TYPED: $_FALLTHROUGH;
        case Module::Phase::COMPILED: break;

        // if the module has already been exported, then we wait for the result
        default: return module->metadata<Module::Phase::EXPORTED>()->deferred();
    }

    // check how many errors have occurred now
    auto errors = module->reporter()->errors();

    // stop when the module has any incoming errors
    if (errors) return isolate->panic(8000001, resource.relative(), errors), nullptr;

    // ensure the module has been suitably compiled as well
    if (!module->ready()) module->compile(m_services);

    // get the runtime options instance
    auto* options = isolate->options();

    // allow dumping our details of the modules
    if (options->dump.syntax) module->dump<Module::Dump::SYNTAX>();
    if (options->dump.types) module->dump<Module::Dump::TYPEDEFS>();
    if (options->dump.bytecode) module->dump<Module::Dump::BYTECODE>();

    // attempt interpretting the result now
    return module->interpret(isolate, trace);
}

Talos::Resource::Result Talos::Import::Service::resolve(
    const $::String::View& script, const $::Filesystem::Path& hint) {
    auto result = Resource::Path::resolve(script, hint);
    if (!result.has_value()) return result;  // exit early

    auto resource = result.value();  // get the resource to be used
    if (resource.scheme() != $::URI::Scheme::FILE) return resource;

    // get the associated file_path
    auto file_path = $::Path::canonical(resource.body());

    // if we have a non-crate then return immediately
    if ($::Path::filename(file_path) != Crate::Constants::filename()) return resource;

    // otherwise get the associated crate to be used
    auto* crate = m_services->get<Crate::Service>()->resolve(file_path);
    if (auto main = crate->main()) return resolve(main->body(), crate->path());
    return std::unexpected(Diagnostic::Traits::format(8000100, resource.relative()));
}

//  PRIVATE METHODS  //

Talos::Module::Interface* Talos::Import::Service::m_prepare(Module::Interface* module) const {
    if (module == nullptr) return module;  // passthrough
    if (module->phase() >= Module::Phase::PARSED) return module;
    return module->parse(m_services), module;  // parse now
}
