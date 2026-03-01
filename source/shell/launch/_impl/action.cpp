/// Shell Modules
#include "shell/launch/action.hpp"

//  X-MACROS  //

#define XX_OPTIONS_LIST(X)                           \
    SHELL_XX_OPTIONS_LAUNCH(X)                       \
    X("", "")                                        \
    X("--verbose", "Shows verbose analysis outputs") \
    X("", "")                                        \
    SHELL_XX_OPTIONS_COMMON(X)

//  CONSTRUCTORS  //

Shell::Launch::Action::Action() : Abstract("run") {
#define X(N, D, ...) { $::ANSI(N), D },
    m_descriptor.positionals({ { "script", false }, { "argv...", false } }).options({ XX_OPTIONS_LIST(X) });
#undef X
}

//  PRIVATE METHODS  //

void Shell::Launch::Action::m_execute() {
    // get some details about the arguments
    auto begin = m_options.script.argv.begin();
    auto end = m_options.script.argv.end();
    auto dashes = std::find(begin, end, "--");

    // remove any items before and including the dashes
    if (dashes != end) m_options.script.argv.erase(begin, dashes + 1);

    // attempt running the runtime now
    auto exit_code = Talos::Toolchain::launch(m_options);
    if (exit_code) throw CLI::RuntimeError(exit_code);
}

void Shell::Launch::Action::m_subscribe(CLI::App* command) {
    // we allow all positionals to get passed through
    command->positionals_at_end(true);

    // bind all the common options
    m_common(command, &m_options, true);

    // bind some launch only options here
    command->add_flag("--verbose", m_options.flags.verbose);

    // prepare the positionals that will be available now
    command->add_option("script.tal", m_options.script.entry);
    command->add_option("argv", m_options.script.argv);

    // set the necessary callback to run the instance now
    command->callback(std::bind(&Action::m_execute, this));
}
