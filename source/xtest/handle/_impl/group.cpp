/// XT Includes
#include "xtest/handle/group.hpp"
#include "xtest/assert/reason.hpp"
#include "xtest/session/runner.hpp"

//  PUBLIC METHODS  //

void XT::Group::execute(Session::Runner* runner) const {
    // destructure some common items now
    auto* reporter = runner->reporter();

    // begin the group section
    reporter->group_opened(this);

    // determine if skipping this group at all
    auto skip = !m_initialize(runner) || m_meta->skip || m_meta->todo;

    // allow testing if the group is not skipped or unimplemented
    for (size_t ii = 0; !skip && ii < m_tests.size(); ++ii) m_tests[ii]->execute(runner);

    // close the group section
    reporter->group_closed(this);
}

//  PRIVATE METHODS  //

bool XT::Group::m_initialize(Session::Runner* runner) const {
    // stop immediately if valid at all
    if (m_setup == nullptr) return true;

    // clang-format off
    try { return m_setup(runner), true; } // validly setup the group
    catch (...) { return runner->reporter()->group_failure(this, Assert::Reason::translate()), false; }
    // clang-format on
}
