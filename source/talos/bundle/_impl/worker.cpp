/// Talos Modules
#include "talos/bundle/worker.hpp"
#include "talos/bundle/service.hpp"
#include "talos/document/buffer.hpp"
#include "talos/lifecycle/service.hpp"
#include "talos/linker/arena.hpp"
#include "talos/module/service.hpp"

//  CONSTRUCTORS  //

Talos::Bundle::Worker::Worker(const Options& options) : Main(), m_options(options) {}
Talos::Bundle::Worker::Worker(XI::Container* services, const Options& options) :
    Main(services), m_archive(services), m_options(options) {}

//  PRIVATE METHODS  //

$_NORETURN void Talos::Bundle::Worker::m_execute() {
    // prepare the baseline spinner suffix to be shown
    auto suffix = [](const $::String::View& message) {
        auto prefix = $::Convert::stringify($::Dye::green("Bundling"));
        return prefix + ": " + $::Convert::stringify($::Dye::dim(message));
    };

    // force our runtime to preload the lifecycle now
    $_UNUSED $_AUTO = service<Lifecycle::Service>()->scope(this);

    // prepare the necessary services to be used
    auto* async = service<Async::Service>();
    auto* runtime = service<Runtime::Options>();
    auto* modules = service<Import::Service>();

    // get an initial starting time-point
    auto start = $::Clock::Performance();

    // start by resolving the underlying script
    auto script = m_resolve(runtime->script.entry);
    auto reporter = service<Diagnostic::Reporter>();

    // attempt running analysis now
    auto stats = runtime->flags.typeless ? Import::Statistics() : modules->analyze(script, reporter.get(), true);

    // attempt checking the types available now as necessary
    if (stats.errors) m_thread->shutdown($_EXIT_FAILURE);

    // stop if in linting only mode
    if (!m_options.compile) m_thread->shutdown($_EXIT_SUCCESS);
    else if (stats.hints) $::IO::println();  // display padding

    // construct the necessary spinner now
    if (runtime->flags.verbose) m_spinner = async->spinner(suffix("Compiling Modules..."));

    // now we want to go through every file and archive them
    auto blob = m_archive.encode(modules);

    // declare as actually imbuing the executable now
    if (runtime->flags.verbose) m_spinner->suffix(suffix("Imbuing Executable..."));

    // get the underlying executable binary now and imbue it
    auto binary = XJCT::Archive::Binary($::Executable::resolve());
    if (!m_imbue(binary, blob)) m_thread->shutdown($_EXIT_FAILURE);

    // finally show that we are writing out output
    if (runtime->flags.verbose) m_spinner->suffix(suffix("Writing Executable..."));

    // get the incoming output name to be used
    auto output = m_output(script, binary.extension());

    // attempt outputting the file with the desired options now
    $::Filesystem::Overwrite(output, binary.buffer());

    // make the output file also executable now as well
    $::Filesystem::Chmod.executable(output);

    // finally attempt code-signing if necessary
    if (!m_codesign(output)) m_thread->shutdown($_EXIT_FAILURE);

    // immediately stop if not in verbose mode
    if (!runtime->flags.verbose) m_thread->shutdown($_EXIT_SUCCESS);

    // prepare the elapsed time now
    auto details = fmt::format("Compiled '{0}' in {1}", output.filename().string(), $::Clock::Performance() - start);

    // finally we dismiss with the time elapsed and exit the worker now
    m_spinner->dismiss(suffix(details)), m_thread->shutdown($_EXIT_SUCCESS);
}

$::URI::Buffer Talos::Bundle::Worker::m_resolve(const $::String::View& script) {
    auto resource = resolve(script, $::System::cwd());
    if (resource.has_value()) return *resource;
    m_failure(8000000, resource.error());
    m_thread->shutdown($_EXIT_FAILURE);
}

$::Filesystem::Path Talos::Bundle::Worker::m_output(const $::URI::View& script) {
    return m_output(script, XJCT::Archive::Extension);
}

$::Filesystem::Path Talos::Bundle::Worker::m_output(const $::URI::View& script, const $::String::View& extension) {
    // prepare the baseline output to be used now
    auto output = m_options.output.size() ? $::Path::canonical(m_options.output)
                                          : $::Filesystem::Path(script.body()).replace_extension();

    // and handle deciding the correct extension to be used now
    return extension.size() && output.extension() != extension ? output += extension : output;
}

bool Talos::Bundle::Worker::m_codesign(const $::Filesystem::Path& output) const noexcept {
    return m_archive.provider()->codesign(output) || m_failure(9000902, $::Path::relative(output).string());
}

bool Talos::Bundle::Worker::m_imbue(Executable& binary, const Buffer& buffer) const noexcept {
    return m_imbue(binary, Blob(reinterpret_cast<const char*>(buffer.data()), buffer.size()));
}

bool Talos::Bundle::Worker::m_imbue(Executable& binary, const Blob& blob) const noexcept {
    if (!m_archive.provider()->imbue(binary, { Fuse::BUNDLED.name(), blob })) return m_failure(9000900);
    return m_archive.provider()->infuse(binary, Fuse::BUNDLED) || m_failure(9000901, Fuse::BUNDLED.name());
}
