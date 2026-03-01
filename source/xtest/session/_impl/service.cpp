/// XT Modules
#include "xtest/session/service.hpp"
#include "xtest/session/registry.hpp"
#include "xtest/session/runner.hpp"

//  PUBLIC METHODS  //

int32_t XT::Session::Service::launch(const $::Dict<Group*>& sections) {
    // prepare a current test-runner to be used
    auto runner = m_services->get<Runner>();

    // prepare caching the runner instance for external use potentially
    $_UNUSED $_AUTO = (m_runner = runner.get(), $::Functor::Defer([&] { m_runner = nullptr; }));

    // pull some common runner variables out
    auto total = sections.size();
    auto* options = runner->options();
    auto* reporter = runner->reporter();

    // iterate over the sections now to be executed with a count as well
    auto start = (reporter->before_running(total, options), $::Chrono::Point());
    for (const auto& section : sections | std::views::values) section->execute(runner.get());
    reporter->after_running(total, $::Chrono::Point() - start);  // finished

    // get the final success result to be shown
    return runner->statistics()->success() ? $_EXIT_SUCCESS : $_EXIT_FAILURE;
}
