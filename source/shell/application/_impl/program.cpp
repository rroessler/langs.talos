/// Shell Modules
#include "shell/application/program.hpp"

//  CONSTRUCTORS  //

Shell::Program::Program() : m_app($::New().unique<CLI::App>()) {
    // set the application now
    m_app->name(TALOS_MM_IDENTIFIER);

    // ensure we receive a subcommand
    m_app->require_subcommand(0, 1);

    // set a desired formatter now
    m_app->formatter($::New().shared<Formatter>(this));

    // set the underlying version handler now as well
    m_app->set_version_flag("-v,--version", "v" TALOS_MM_VERSION);
    m_app->add_flag_callback("--vendors", m_vendors)->configurable(false);
    m_app->add_flag_callback("--revision", m_revision)->configurable(false);

    // process global environment variables early
    if (auto color = $::Environment::get("NO_COLOR")) m_color(*color);
    if (auto spinners = $::Environment::get("NO_PROGRESS")) m_progress(*spinners);
    if (auto level = $::Environment::get("TALOS_LOGGING_LEVEL")) m_level(*level);
}

//  PUBLIC METHODS  //

int32_t Shell::Program::launch(int32_t argc, char** argv) {
    // fast-path our "help" screen when no arguments are given
    if (argc < 2) return m_help($::IO::cout()), $_EXIT_SUCCESS;

    // attempt parsing now
    CLI11_PARSE(*m_app, argc, argv);

    // and declare our result as a success now
    return $_EXIT_SUCCESS;
}

//  PRIVATE METHODS  //

void Shell::Command::Abstract::m_common(CLI::App* command, Talos::Runtime::Options* options, bool runtime) {
    // prepare some common environment/internal items now
    auto& stack_size = options->async.thread.stack_size;
    auto& stack_limit = options->async.thread.stack_limit;
    auto& hardware_limit = options->async.vprocs.hardware_limit;

    command->add_option("--internal-stack-size", stack_size)->envname("TALOS_STACK_SIZE");
    command->add_option("--internal-stack-limit", stack_limit)->envname("TALOS_STACK_LIMIT");
    command->add_option("--internal-hardware-vprocs", hardware_limit)->envname("TALOS_HARDWARE_VPROCS");

    // if not if runtime mode, then stop handling
    if (!runtime) return;

    // add the linting flag to be used now
    command->add_flag("--lint", options->flags.lint);

    auto hints = [severity = &options->diagnostics.severity] { *severity = Talos::Diagnostic::Severity::HINT; };
    command->add_flag_callback("--hints", hints);  // allows showing additional linting details where possible

    // prepare the baseline runtime flags
    command->add_flag("--optless", options->flags.optless);
    command->add_flag("--jitless", options->flags.jitless);

    // and the dump-based flags to be inherited
    command->add_flag("--dump-syntax", options->dump.syntax);
    command->add_flag("--dump-graphs", options->dump.graphs);
    command->add_flag("--dump-bytecode", options->dump.bytecode);
    command->add_flag("--dump-assembly", options->dump.machine);
}

void Shell::Program::m_level(const $::String::View& level) {
    $::Logger::Options::update($::Logger::Options::resolve(level));
}

void Shell::Program::m_color(const $::String::View& color) {
    auto enabled = color.empty() || color == "0";  // determine enablement
    auto mode = enabled ? $::Logger::Color::AUTO : $::Logger::Color::NEVER;
    $::Dye::enabled(enabled), $::Logger::Options::update(mode);
}

void Shell::Program::m_progress(const $::String::View& progress) {
    $::Dye::progress(progress.empty() || progress == "0");
}

void Shell::Program::m_vendors() {
    // prints all the incoming vendor version available
    for (const auto& [name, version] : Talos::Product::vendors()) $::IO::println("{0} - {1}", name, version);

    // and then we want to exit
    throw CLI::Success();
}

void Shell::Program::m_revision() { $::IO::println("v" TALOS_MM_REVISION), throw CLI::Success(); }
