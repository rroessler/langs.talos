/// Testing Includes
#include "xtest/reporter/abstract.hpp"
#include "xtest/session/runner.hpp"

//  PRIVATE METHODS  //

XT::Assert::Trace &XT::Reporter::Abstract::m_trace() { return m_runner->asserts()->m_trace; }
const XT::Assert::Trace &XT::Reporter::Abstract::m_trace() const { return m_runner->asserts()->m_trace; }

XT::Trivia::Statistics &XT::Reporter::Abstract::m_stats() { return *m_runner->statistics(); }
const XT::Trivia::Statistics &XT::Reporter::Abstract::m_stats() const { return *m_runner->statistics(); }

XT::Assert::Pending &XT::Reporter::Abstract::m_pending() { return m_runner->asserts()->m_failures; }
const XT::Assert::Pending &XT::Reporter::Abstract::m_pending() const { return m_runner->asserts()->m_failures; }
