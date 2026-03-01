/// Vendor Modules
#include <xtest/xtest.hpp>

/**
 * @brief Testing runtime entry-point.
 * @param argc                  Argument count.
 * @param argv                  Variadic arguments.
 */
int32_t main(int32_t, char**) {
    // initialize "stdio" handling now
    $_UNUSED $_AUTO = $::Stream::Setup();

    // prepare the base services available
    auto services = XI::Container();

    // attempt binding all the desired services
    auto* options = services.emplace<XT::Session::Options>();

    // enabled running any benchmarks
    options->bench.enabled = true;

    // update the options if necessary to do so
    options->spinner = [](XI::Container*) {
        static $::Spinner::Options s_options = {};  // prepare
        return $::New().unique<$::Spinner::Basic>(s_options);
    };

    // get the session service now
    auto* session = services.emplace<XT::Session::Service>();

    // and attempt launching now
    return session->launch(XT::Session::Registry::sections());
}
