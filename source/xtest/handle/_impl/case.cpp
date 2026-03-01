/// XT Includes
#include "xtest/handle/case.hpp"
#include "xtest/assert/reason.hpp"
#include "xtest/session/runner.hpp"

//  PUBLIC METHODS  //

void XT::Case::execute(Session::Runner* runner) const {
    // destructure some common items now
    auto* reporter = runner->reporter();

    // declare as currently started now
    reporter->test_starting(this);

    // if skipping then declare as such now
    if (m_meta->skip) return reporter->test_skipped(this);
    if (m_meta->todo) return reporter->test_unimplemented(this);

    // clang-format off
    try { reporter->test_success(this, $::Clock::Measure([&] { m_callback(runner); })); }
    catch (const Assert::Timeout&) { reporter->test_timeout(this, runner->options()->bench.timeout); }
    catch (...) { reporter->test_failure(this, Assert::Reason::translate()); }
    // clang-format on
}
