/// Shell Modules
#include "shell/application/program.hpp"

/// Shell Actions
#include "shell/bundle/action.hpp"
#include "shell/format/action.hpp"
#include "shell/launch/action.hpp"
#include "shell/lint/action.hpp"
#include "shell/serve/action.hpp"
#include "shell/task/action.hpp"
#include "shell/test/action.hpp"
#include "shell/upgrade/action.hpp"

/**
 * @brief Talos runtime entry-point.
 * @param argc                  Argument count.
 * @param argv                  Variadic arguments.
 */
int32_t main(int32_t argc, char** argv) {
    // initialize "stdio" handling now
    $_UNUSED $_AUTO = $::Stream::Setup();

    // if the bundle fuse has been set, then we should immediately launch the runtime
    if (Talos::Fuse::BUNDLED.exists()) return Talos::Toolchain::launch(argc, argv);

    // construct the underlying program
    auto program = Shell::Program();

    // subscribe all the available actions now
    program.subscribe<Shell::Launch::Action>();
    program.subscribe<Shell::Task::Action>();
    program.subscribe<Shell::Test::Action>();

    program.subscribe<Shell::Bundle::Action>();
    program.subscribe<Shell::Format::Action>();
    program.subscribe<Shell::Lint::Action>();
    program.subscribe<Shell::Serve::Action>();

    program.subscribe<Shell::Upgrade::Action>();

    // and finally launch the program
    return program.launch(argc, argv);
}
