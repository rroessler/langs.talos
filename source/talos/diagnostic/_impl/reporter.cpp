/// Talos Modules
#include "talos/diagnostic/reporter.hpp"
#include "talos/crate/registry.hpp"
#include "talos/runtime/options.hpp"

//  CONSTRUCTORS  //

Talos::Diagnostic::Reporter::Reporter(const $::URI::View& resource) : Reporter(Options(), resource) {}

Talos::Diagnostic::Reporter::Reporter(const Options& options, const $::URI::View& resource) :
    m_resource(resource), m_options($::New().unique<Options>(options)) {
    auto crate = Crate::Registry::scan(resource);  // get now
    if (crate) m_options->overrides = crate->lint().overrides;
}

Talos::Diagnostic::Reporter::Reporter(XI::Container* services, const $::URI::View& resource) :
    Reporter(services->get<Runtime::Options>()->diagnostics, resource) {}

//  PRIVATE METHODS  //

void Talos::Diagnostic::Reporter::m_print($::Stream::Output& os, const Reporter& self) {
    for (const auto& [ii, diagnostic] : $::Each(self.m_diagnostics)) {
        os << diagnostic;  // show the diagnostic and ending
        if (ii < self.m_diagnostics.size() - 1) os << "\n\n";
    }
}
