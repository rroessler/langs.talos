/// Testing Includes
#include "xtest/assert/that.hpp"
#include "xtest/session/runner.hpp"

//  PRIVATE METHODS  //

bool XT::Assert::That::m_hook(bool result, const Info &info) {
  // get the underlying reporter instance now
  auto *reporter = m_runner->reporter();

  // attempt showing the assertion details
  reporter->assertion_starting(info);

  // handle the incoming assertion details now
  if (!result) reporter->assertion_failure(info);
  else reporter->assertion_teardown(info, result);

  // otherwise we declare that a failure occured if necessary
  return result;
}
