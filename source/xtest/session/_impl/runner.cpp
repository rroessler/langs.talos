/// XT Modules
#include "xtest/session/runner.hpp"
#include "xtest/reporter/facade.hpp"

//  CONSTRUCTORS  //

XT::Session::Runner::Runner(XI::Container* services) : Runner(services->get<Options>()) {
    m_services = services;  // bind the services now to be used
}

XT::Session::Runner::Runner(Options* options) : m_options(options) {
    $_ASSERT(m_options, "Session::Runner requires valid options");  // prepare
    m_reporter = $::New().unique<Reporter::Facade>(m_options->reporter, this);
}
