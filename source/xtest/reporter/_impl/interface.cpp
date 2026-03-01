/// XT Modules
#include "xtest/reporter/interface.hpp"
#include "xtest/session/runner.hpp"

size_t& XT::Reporter::Interface::m_depth() { return m_runner->depth(); }
size_t XT::Reporter::Interface::m_depth() const { return m_runner->depth(); }

XT::Assert::Trace& XT::Reporter::Interface::m_trace() { return m_runner->asserts()->m_trace; }
const XT::Assert::Trace& XT::Reporter::Interface::m_trace() const { return m_runner->asserts()->m_trace; }

XT::Session::Statistics& XT::Reporter::Interface::m_stats() { return *m_runner->statistics(); }
const XT::Session::Statistics& XT::Reporter::Interface::m_stats() const { return *m_runner->statistics(); }

XT::Assert::Pending& XT::Reporter::Interface::m_pending() { return m_runner->asserts()->m_failures; }
const XT::Assert::Pending& XT::Reporter::Interface::m_pending() const { return m_runner->asserts()->m_failures; }

$::Spinner::Shared XT::Reporter::Interface::m_loader() const {
    return m_runner->options()->spinner(m_runner->service<XI::Container>());
}
