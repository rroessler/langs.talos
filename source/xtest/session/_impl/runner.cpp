/// XT Modules
#include "xtest/session/runner.hpp"
#include "xtest/reporter/facade.hpp"

//  CONSTRUCTORS  //

XT::Session::Runner::Runner(XI::Container* services) : Runner(*services) { m_services = services; }
XT::Session::Runner::Runner(Options* options) : m_options(options) {
    $_ASSERT(m_options, "Session::Runner requires valid options");  // prepare
    m_reporter = $::New().unique<Reporter::Facade>(m_options->reporter, this);
}
