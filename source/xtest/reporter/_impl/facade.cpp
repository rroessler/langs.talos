/// XT Modules
#include "xtest/reporter/facade.hpp"
#include "xtest/session/runner.hpp"

/// XT Reporters
#include "xtest/reporter/_inline/json.hpp"
#include "xtest/reporter/_inline/junit.hpp"
#include "xtest/reporter/_inline/tap.hpp"
#include "xtest/reporter/_inline/text.hpp"
#include "xtest/reporter/_inline/xml.hpp"

/// Forward Declarations
$_FWD(XT::Reporter, $::Ptr::Unique<Reporter::Interface> Factory(Tag, Session::Runner*, $::Stream::Output&))

//  CONSTRUCTORS  //

XT::Reporter::Facade::Facade(Tag tag, Session::Runner* runner) : Interface(runner) {
    // attempt resolving a suitable output stream now

    // and finally resolving a suitable proxy instance
    m_proxy = Factory(tag, runner, m_stream ? *m_stream.get() : $::IO::cout());

    switch (tag) {
#define X(T, V, ...) \
    case Tag::T: m_verbose = V; break;
        XTEST_XX_REPORTERS_LIST(X)
#undef X
    }
}

//  PUBLIC METHODS  //

$::Ptr::Unique<XT::Reporter::Interface> XT::Reporter::Factory(
    Tag tag, Session::Runner* runner, $::Stream::Output& output) {
    switch (tag) {
#define X(T, ...) \
    case Tag::T: return $::New().unique<Proxy<Tag::T>>(runner, output);
        XTEST_XX_REPORTERS_LIST(X)
#undef X
    }
}
