/// Testing Includes
#include "xtest/reporter/facade.hpp"
#include "xtest/session/runner.hpp"

//  CONSTRUCTORS  //

XT::Reporter::Facade::Facade(Session::Runner *runner) :
    Abstract(runner), m_proxy(runner->options()->reporter.factory(runner)) {}
