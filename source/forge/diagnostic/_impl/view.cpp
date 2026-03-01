/// Forge Modules
#include "forge/diagnostic/view.hpp"

//  PRIVATE METHODS  //

void Forge::Diagnostic::View::m_print($::Stream::Output& os, const View& self) {
    auto severity = Traits::color(self.m_severity);
    auto code = $::Dye::grey("(TAL{0})", self.m_code);

    os << severity << ' ' << code << ": " << self.m_message << '\n';  // prepare details
    os << $::Dye::grey(" --> {0}", fmt::to_string(fmt::join(std::views::reverse(self.m_stack), "\n --> ")));
}
