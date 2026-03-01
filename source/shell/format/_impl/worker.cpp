/// Shell Modules
#include "shell/format/action.hpp"

//  PRIVATE METHODS  //

Shell::Format::Result Shell::Format::Action::m_worker(const $::URI::Buffer& resource) const {
    auto buffer = Talos::Document::Buffer(resource);
    return Talos::Toolchain::format(buffer, m_options);
}

void Shell::Format::Action::m_overwrite(const $::URI::View& resource, const Result& result) const {
    // handle when errors occur firstly
    if (!result.has_value()) return m_fail("Failed to format '{0}'", resource.relative());

    // otherwise write to the actual file in question now as needed
    $::Filesystem::Overwrite(resource.body(), *result);
}

void Shell::Format::Action::m_output(const $::URI::View& resource, const Result& result, bool edits) const {
    // handle based on the edits details now
    if (!edits) return result ? $::IO::print(*result) : m_fail("Failed to format '{0}'", resource.relative());

    // if we failed to parse, the declare a "null" result for JSON edits
    if (!result.has_value()) return $::IO::println($::JSON::stringify($::Serde::Null()).value());

    /// TODO: otherwise convert the result into suitable edits to be used
    $_ABORT("Unimplemented --json formatter edits");
}
